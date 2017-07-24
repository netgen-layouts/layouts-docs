Creating custom parameter types
===============================

Netgen Layouts ships with around 15 parameter types which you can use in your
custom blocks and queries and which fulfill most of the everyday usecases.

However, if you need custom validation on some of your parameters, or custom
display in Symfony forms, you need to create a custom parameter type.

We will show how to create a custom parameter type on an example of a parameter
which stores and validates dates in `Google Analytics format`_.

There are two parts to implementing a parameter type in Netgen Layouts:

* Implementing a main parameter type service which deals with parameter value
  conversion and validation
* Implementing a form mapper which takes care of creating a Symfony form for the
  parameter type

Implementing the parameter type service
---------------------------------------

Parameter type service needs to implement
``Netgen\BlockManager\Parameters\ParameterTypeInterface``. Since this interface
has a handful of methods, there is a handy abstract class from which you can
extend so you don't have to write boilerplate code in your parameter types.

This cuts down the number of required methods to implement to 2. Let's create
an empty class extending the abstract class:

.. code-block:: php

    <?php

    namespace AppBundle\Parameters\ParameterType;

    use Netgen\BlockManager\Parameters\ParameterInterface;
    use Netgen\BlockManager\Parameters\ParameterType;

    class GoogleAnalyticsDateType extends ParameterType
    {
        /**
         * Returns the parameter type identifier.
         *
         * @return string
         */
        public function getIdentifier()
        {
        }

        /**
         * Returns constraints that will be used to validate the parameter value.
         *
         * @param \Netgen\BlockManager\Parameters\ParameterInterface $parameter
         * @param mixed $value
         *
         * @return \Symfony\Component\Validator\Constraint[]
         */
        protected function getValueConstraints(ParameterInterface $parameter, $value)
        {
        }
    }

As you can see, only two methods need to be implemented for basic parameter type
to work: ``getIdentifier``, which should return a unique identifier of a
parameter type, and ``getValueConstraints``, which should return an array of
Symfony validator constraints which validate the value.

.. note::

    Every parameter type needs to allow ``null`` as its value, since parameters
    are by default optional in blocks and queries. Because of that, take care
    **not to include** constraints which validate that the value is not ``null``,
    like ``NotNull`` or ``NotBlank``.

    To specify constraints when the parameter is required, you can use the
    ``getRequiredConstraints`` method. It already has a default implementation
    which you can override to suit your needs.

Let's implement ``getIdentifier`` and ``getValueConstraints`` methods:

.. code-block:: php

    /**
     * Returns the parameter type identifier.
     *
     * @return string
     */
    public function getIdentifier()
    {
        return 'ga_date';
    }

    /**
     * Returns constraints that will be used to validate the parameter value.
     *
     * @param \Netgen\BlockManager\Parameters\ParameterInterface $parameter
     * @param mixed $value
     *
     * @return \Symfony\Component\Validator\Constraint[]
     */
    protected function getValueConstraints(ParameterInterface $parameter, $value)
    {
        return array(
            new Constraints\Type(array('type' => 'string'))
        );
    }

With the above implementation, we specified that the unique identifier of our
parameter type is ``ga_date`` and that the value of the parameter should be a
string.

This is a good time to add any custom validations you want, for example, you can
implement a validator and a constraint that validates the date as a
Google Analytics date.

The purpose of other methods in ``ParameterTypeInterface`` is detailed below:

``configureOptions``

    This method uses the Symfony OptionsResolver component to specify any custom
    options your parameter type might have. Here, you can use the full power of
    the component to define required and optional options, custom validation and
    so on. For example, you might specify the minimum year your parameter
    accepts and then use the option in ``getValueConstraints`` method to modify
    the value constraints accordingly. An example implementation might look like
    this:

    .. code-block:: php

        public function configureOptions(OptionsResolver $optionsResolver)
        {
            $optionsResolver->setDefault('min_year', null);
            $optionsResolver->setRequired(array('min_year'));
            $optionsResolver->setAllowedTypes('min_year', array('int', 'null'));
        }

``getConstraints``

    This method by default takes the constraints from ``getValueConstraints``
    and ``getRequiredConstraints`` method, and merges them together. Notice that
    this method has public visibility, while ``getValueConstraints`` and
    ``getRequiredConstraints`` are protected. This means that this method is the
    one used by Netgen Layouts when validating the parameter value and if you
    override it, you will effectively override any constraints implemented in
    the two protected methods.

``toHash``

    This method is responsible for converting the parameter value to a hash
    format (scalar or an array of scalars). Since every parameter value is
    stored in the database encoded into JSON, this method must not return any
    data that cannot be safely encoded into JSON. Default implementation does
    not convert the value and simply returns it as is.

``fromHash``

    This method does the opposite of ``toHash`` method. That is, it converts the
    JSON decoded data stored in the database to a value that will be used by the
    rest of Netgen Layouts code as well as your custom code. This can be
    anything really: a scalar, an array, on object or a whole object graph.
    Default implementation does not convert the value and simply returns it as
    is.

``isValueEmpty``

    This method is used to signal to the system when the value of the parameter
    is considered empty. For example, a date can be empty if the value of the
    parameter is ``null`` or an empty string. By default, this method uses
    ``empty`` PHP language construct to check emptiness of the value.

Implementing the form mapper
----------------------------

Form mapper object is responsible for specifying how the parameter will look
like on a Symfony form. The interface
``Netgen\BlockManager\Parameters\Form\MapperInterface`` provides three methods
for you to implement. There is also an abstract class which you can extend to
ease the implementation, so you need to implement only one method.

Basic form mapper needs to only specify which Symfony form type to use:

.. code-block:: php

    <?php

    namespace AppBundle\Parameters\FormMapper;

    use Netgen\BlockManager\Parameters\Form\Mapper;
    use Symfony\Component\Form\Extension\Core\Type\TextType;

    class GoogleAnalyticsDateMapper extends Mapper
    {
        /**
         * Returns the form type for the parameter.
         *
         * @return string
         */
        public function getFormType()
        {
            return TextType::class;
        }
    }

The purpose of other methods in ``MapperInterface`` is detailed below:

``mapOptions``

    If your parameter type has custom options which need to be forwarded to
    Symfony form type, you can use this method to do so. For example, if you
    implemented a custom Symfony form type for your Google Analytics date, you
    could transfer your ``min_year`` option to the Symfony form, so it does not
    allow specifying any year lower than what is defined in your option.

``handleForm``

    This method is a generic method which receives the form built from the
    information in ``getFormType`` and ``mapOptions`` methods and makes it
    possible to do anything you wish with the form, like attaching custom data
    mappers or data transformers, adding event listeners to the form and so on.

    Basically, anything you can do in Symfony form type class with a form field,
    you can do here too.

Registering the Symfony services
--------------------------------

To activate both the parameter type and the form mapper, you need to specify
them as Symfony services.

Parameter type service needs to have a
``netgen_block_manager.parameters.parameter_type`` tag in its service
definition, while the form mapper needs to have a
``netgen_block_manager.parameters.form.mapper`` tag, together with the ``type``
attribute whose value is equal to the parameter type identifier.

Our parameter type and form mapper service definitions should look like this:

.. code-block:: yaml

    services:
        app.parameters.parameter_type.ga_date:
            class: AppBundle\Parameters\ParameterType\GoogleAnalyticsDateType
            tags:
                - { name: netgen_block_manager.parameters.parameter_type }

        app.parameters.form.mapper.ga_date:
            class: AppBundle\Parameters\FormMapper\GoogleAnalyticsDateMapper
            tags:
                - { name: netgen_block_manager.parameters.form.mapper, type: ga_date }

.. _`Google Analytics format`: https://developers.google.com/analytics/devguides/reporting/core/v3/reference#startDate
