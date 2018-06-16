Creating custom target types
============================

Netgen Layouts is shipped with a number of target types to which you can map
your layouts to be used in a layout resolving process. These target types are
generic, allowing you to attach a layout to a request URI, a Symfony route or
their prefixes. In most cases, when working with pure Symfony apps, this is
enough.

However, if you wish that your layouts can be mapped to domain objects from your
CMS directly, you can create custom target types.

.. note::

    Custom target type can be whatever comes to mind, not only a domain object
    from your CMS.

.. warning::

    Custom target types are one of the most complicated extension points in
    Netgen Layouts and creating a custom target type involves creating
    configuration, templates, translations and quite a bit of code.

Implementing the target type classes
------------------------------------

Implementing a target type in PHP requires creating at least three Symfony
services:

* Target type itself
* Symfony form mapper
* A target handler for every database engine supported in Netgen Layouts

Creating a target type
~~~~~~~~~~~~~~~~~~~~~~

A target type is a PHP class implementing
``Netgen\BlockManager\Layout\Resolver\TargetTypeInterface``. The purpose of this
class is twofold:

* Provide Symfony constraints that validate the value of the target when adding
  it to a mapping
* Extract the value of the target from the request to be used in layout
  resolving process

The first point is achieved by implementing ``getConstraints`` method, which
should return the array of Symfony validator constraints which should validate
the value. For example, in eZ location target type, these constraints validate
that the ID of the location is a number larger than 0 and that the location with
the provided ID actually exists:

.. code-block:: php

    public function getConstraints(): array
    {
        return array(
            new Constraints\NotBlank(),
            new Constraints\Type(array('type' => 'numeric')),
            new Constraints\GreaterThan(array('value' => 0)),
            new EzConstraints\Location(),
        );
    }

The second point is achieved by implementing the ``provideValue`` method. This
method takes a request object and should return a value of your target type if
it exists in the request or ``null`` if it doesn't. For example, eZ location
target type extracts the location from provided request and returns its ID:

.. code-block:: php

    public function provideValue(Request $request)
    {
        $location = $this->contentExtractor->extractLocation($request);

        return $location instanceof APILocation ? $location->id : null;
    }

The one method that remains to be implemented is the ``getType`` method, which
should return a unique identifier of the target type.

Once this is done, we need to register the target type in the Symfony DIC with
the ``netgen_block_manager.layout.resolver.target_type`` tag:

.. code-block:: yaml

    app.target_type.my_target:
        class: AppBundle\Layout\Resolver\TargetType\MyTarget
        tags:
            - { name: netgen_block_manager.layout.resolver.target_type }

.. tip::

    You can add a ``priority`` attribute to the tag, which allows you to make
    your target type considered before others when deciding if the current
    request matches one of the targets.

Creating the form mapper
~~~~~~~~~~~~~~~~~~~~~~~~

To be able to add the target to a mapping or edit the value of an existing
target, you need to provide a form mapper which provides data for generating
Symfony form for your target type. The mapper needs to implement
``Netgen\BlockManager\Layout\Resolver\Form\TargetType\MapperInterface`` and
there's also a handy abstract class which you can extend to cut down the number
of methods to define to one: ``getFormType``, which returns which Symfony form
type should be used to edit the target:

.. code-block:: php

    <?php

    declare(strict_types=1);

    namespace AppBundle\Layout\Resolver\Form\TargetType\Mapper;

    use Netgen\BlockManager\Layout\Resolver\Form\TargetType\Mapper;
    use Symfony\Component\Form\Extension\Core\Type\TextType;

    final class MyTarget extends Mapper
    {
        public function getFormType(): string
        {
            return TextType::class;
        }
    }

There are two other methods in the interface:

* ``getFormOptions`` which makes it possible to provide custom options to the form type
* ``handleForm`` which allows you to customize the form in any way you see fit

Finally, you need to register the mapper in the Symfony container with the
correct tag and the identifier of the target type:

.. code-block:: yaml

    app.layout.resolver.form.target_type.mapper.my_target:
        class: AppBundle\Layout\Resolver\Form\TargetType\Mapper\MyTarget
        tags:
            - { name: netgen_block_manager.layout.resolver.form.target_type.mapper, target_type: my_target }

Creating target handlers for the database engine
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Matching the target value from the request to the value stored in the database
is done in the database itself. This means that you need to provide a so called
target handler for every database engine supported in Netgen Layouts.

The only supported database engine is called "doctrine", since it uses Doctrine
library to communicate with the database.

This target handler needs to implement
``Netgen\BlockManager\Persistence\Doctrine\QueryHandler\TargetHandlerInterface``
interface which provides a single method called ``handleQuery`` which takes the
Doctrine query object and the target value and should modify the query in way to
match the provided value.

Stored target value can be accessed in the query with ``rt.value`` so to match a
simple integer, you would implement it like this:

.. code-block:: php

    public function handleQuery(QueryBuilder $query, $value)
    {
        $query->andWhere(
            $query->expr()->in('rt.value', array(':target_value'))
        )
        ->setParameter('target_value', $value, \Doctrine\DBAL\Connection::PARAM_INT_ARRAY);
    }

Finally, the target handler needs to registered in the Symfony container with
the correct tag and target type identifier:

.. code-block:: yaml

    app.layout_resolver.target_handler.doctrine.my_target:
        class: AppBundle\LayoutResolver\TargetHandler\Doctrine\MyTarget
        tags:
            - { name: netgen_block_manager.layout.resolver.target_handler.doctrine, target_type: my_target }

Implementing the target type template
-------------------------------------

Target type uses a single template in the ``value`` view context of the
Netgen Layouts view layer to display the value of the target in the admin
interface. Since the target itself usually provides only the scalar identifier
as its value, this template usually needs some logic to display the name of the
target (from your CMS for example). In case of eZ Platform, these templates for
example use Twig functions to load the content and location objects and return
their names and paths:

.. Using html lexer since jinja results in
   "Could not lex literal_block as "jinja". Highlighting skipped." warning !?

.. code-block:: html

    {% set content_name = ngbm_ezcontent_name(target.value) %}

    {{ content_name != null ? content_name : '(INVALID CONTENT)' }}

To register the template in the system, the following configuration is needed
(make sure to use the ``value`` view context):

.. code-block:: yaml

    netgen_block_manager:
        view:
            rule_target_view:
                value:
                    my_target:
                        template: "@App/layout_resolver/target/value/my_target.html.twig"
                        match:
                            rule_target\type: my_target

Target type translations
------------------------

Each target type uses two translation strings, one in ``ngbm`` and one in
``ngbm_admin`` catalog. The first one is a generic string which should provide
a human readable name of the target type and should be in the
``layout_resolver.target.<target_type_identifier>`` format:

.. code-block: yaml

    # ngbm.en.yml

    layout_resolver.target.my_target: 'My target'

The second one is used as a label in administration of interface which states
for which target types is the mapping used and should be in
``layout_resolver.rule.target_header.<target_type_identifier>`` format:

.. code-block: yaml

    # ngbm_admin.en.yml

    layout_resolver.rule.target_header.my_target: 'Applied to My target'
