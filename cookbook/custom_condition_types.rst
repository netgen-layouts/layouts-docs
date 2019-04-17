Creating custom condition types
===============================

Netgen Layouts is shipped with a couple of condition types which you can use to
limit your layout mappings to certain conditions. One example condition type
which is built into Netgen Layouts is the query parameter condition type which
enables the mapping if some query parameter from the request matches the value
stored in the condition. In case of eZ Platform integration, an example
condition type which is built in is the siteaccess condition type that activates
the mapping only if the siteaccess of the current request matches the condition.

If you wish to map your layouts to targets in some other conditions, like time
of day, location of the user, IP address, you name it..., you can create your
own condition types.

.. warning::

    Custom condition types are one of the most complicated extension points in
    Netgen Layouts and creating a custom condition type involves creating
    configuration, templates, translations and quite a bit of code.

Implementing the condition type classes
---------------------------------------

Implementing a condition type in PHP requires creating two Symfony services:

* Condition type itself
* Symfony form mapper

Creating a condition type
~~~~~~~~~~~~~~~~~~~~~~~~~

A condition type is a PHP class implementing
``Netgen\Layouts\Layout\Resolver\ConditionTypeInterface``. The purpose of this
class is twofold:

* Provide Symfony constraints that validate the value of the condition when
  adding it to a mapping
* Deciding if the current request matches the provided value of the condition

The first point is achieved by implementing ``getConstraints`` method, which
should return the array of Symfony validator constraints which should validate
the value. For example, in eZ siteaccess condition type, these constraints
validate that all selected siteaccesses are non empty strings and that they
actually exist:

.. code-block:: php

    public function getConstraints(): array
    {
        return [
            new Constraints\NotBlank(),
            new Constraints\Type(['type' => 'array']),
            new Constraints\All(
                [
                    'constraints' => [
                        new Constraints\Type(['type' => 'string']),
                        new EzConstraints\SiteAccess(),
                    ],
                ]
            ),
        ];
    }

The second point is achieved by implementing the ``matches`` method. This method
takes a request object and based on the data from the request decides if it
matches the provided value. For example, the ``matches`` method of the
eZ siteaccess condition type returns true only if the siteaccess is provided in
the request and is equal to one of the stored values of the condition:

.. code-block:: php

    public function matches(Request $request, $value): bool
    {
        $siteAccess = $request->attributes->get('siteaccess');
        if (!$siteAccess instanceof SiteAccess) {
            return false;
        }

        if (!is_array($value) || count($value) === 0) {
            return false;
        }

        return in_array($siteAccess->name, $value, true);
    }

The one method that remains to be implemented is the ``getType`` method, which
should return a unique identifier of the condition type.

Once this is done, we need to register the condition type in the Symfony DIC
with the ``netgen_block_manager.layout.resolver.condition_type`` tag:

.. code-block:: yaml

    app.condition_type.my_condition:
        class: AppBundle\Layout\Resolver\ConditionType\MyCondition
        tags:
            - { name: netgen_block_manager.layout.resolver.condition_type }

Creating the form mapper
~~~~~~~~~~~~~~~~~~~~~~~~

To be able to add the condition to a mapping or edit the value of an existing
condition, you need to provide a form mapper which provides data for generating
Symfony form for your condition type. The mapper needs to implement
``Netgen\Layouts\Layout\Resolver\Form\ConditionType\MapperInterface`` and
there's also a handy abstract class which you can extend to cut down the number
of methods to define to one: ``getFormType``, which returns which Symfony form
type should be used to edit the condition:

.. code-block:: php

    <?php

    declare(strict_types=1);

    namespace AppBundle\Layout\Resolver\Form\ConditionType\Mapper;

    use Netgen\Layouts\Layout\Resolver\Form\ConditionType\Mapper;
    use Symfony\Component\Form\Extension\Core\Type\TextType;

    final class MyCondition extends Mapper
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
correct tag and the identifier of the condition type:

.. code-block:: yaml

    app.layout.resolver.form.condition_type.mapper.my_condition:
        class: AppBundle\Layout\Resolver\Form\ConditionType\Mapper\MyCondition
        tags:
            - { name: netgen_block_manager.layout.resolver.form.condition_type.mapper, condition_type: my_condition }

Implementing the condition type template
----------------------------------------

Condition type uses a single template in the ``value`` view context of the
Netgen Layouts view layer to display the value of the condition in the admin
interface. Since the condition itself usually provides only the scalar
identifier as its value, this template usually needs some logic to display the
human readable value of the condition. For example, content type condition from
eZ Platform uses custom Twig functions to display content type names instead of
the identifiers:

.. code-block:: jinja

    {% set content_type_names = [] %}

    {% for value in condition.value %}
        {% set content_type_names = content_type_names|merge([ngbm_ez_content_type_name(value)]) %}
    {% endfor %}

    {{ content_type_names|join(', ') }}

To register the template in the system, the following configuration is needed
(make sure to use the ``value`` view context):

.. code-block:: yaml

    netgen_block_manager:
        view:
            rule_condition_view:
                value:
                    my_condition:
                        template: "@App/layout_resolver/condition/value/my_condition.html.twig"
                        match:
                            rule_condition\type: my_condition

Condition type translations
---------------------------

Each condition type uses one translation string in the ``ngbm`` catalog. This is
a generic string which should provide a human readable name of the condition
type and should be in the
``layout_resolver.condition.<condition_type_identifier>`` format:

.. code-block: yaml

    # ngbm.en.yml

    layout_resolver.condition.my_condition: 'My condition'
