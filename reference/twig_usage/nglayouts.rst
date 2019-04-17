``nglayouts``
=============

This global variable has a couple of purposes, three main ones being:

* to provide currently resolved layout to frontend layout templates
* to provide currently resolved layout template to your full views
* to provide a way to load Netgen Layouts configuration in Twig templates
  without having to write custom code

The following is a list of variables available:

``nglayouts.debug``

    This variable defines if Netgen Layouts debug mode is activated. This flag
    is mainly used for development of Netgen Layouts and is not useful in
    normal operation of a website (either in production or development mode).

    To activate Netgen Layouts debug mode, use a configuration similar to this:

    .. code-block:: yaml

        netgen_layouts:
            debug: true

``nglayouts.layout``

    This variable holds the layout resolved in the current request (instance of
    ``Netgen\Layouts\API\Values\Layout\Layout``). It is mostly used in frontend
    layout templates to access the layout and render the zones.

``nglayouts.layoutView``

    This variable holds the layout view of the layout resolved in current
    request (instance of ``Netgen\Layouts\View\View\LayoutViewInterface``). You
    can use it to access any data from the view, like the view context or the
    name of the layout template. If no layout was resolved, this variable will
    be set to ``false`` and if layout resolving process was not ran, it will be
    set to ``null``.

``nglayouts.rule``

    This variable holds the rule (instance of
    ``Netgen\Layouts\API\Values\LayoutResolver\Rule``) that was used to resolve
    the layout for the current request. You can use it to access targets and
    conditions that were responsible for resolving the layout.

``nglayouts.config``

    This variable is an instance of
    ``Netgen\Bundle\LayoutsBundle\Configuration\ConfigurationInterface``. It
    makes it possible to access configuration of Netgen Layouts (basically, any
    container parameter which name starts with ``netgen_layouts.``).

    For example, to access a container parameter called
    ``netgen_layouts.some_config``, you can use
    ``nglayouts.config.parameter('some_config')``.

    .. tip::

        In cases when Netgen Layouts is used on top of eZ Platform, you can use
        this variable to access siteaccess aware container parameters too. For
        example, accessing parameter called
        ``netgen_layouts.cro.some_value`` can be done with the same code
        as before: ``nglayouts.config.parameter('some_config')``.

    In addition to container parameters, this variable makes it possible to
    access the list of entities provided by Netgen Layouts, like block
    definitions, query types and so on. You can access them by using the same
    ``nglayouts.config.parameter()`` function call as before, with the
    parameter names specified below:

    * ``block_definitions`` - Provides a list of all block definitions
    * ``block_types`` - Provides a list of all block types
    * ``block_type_groups`` - Provides a list of all block type groups
    * ``layout_types`` - Provides a list of all layout types
    * ``query_types`` - Provides a list of all query types
    * ``value_types`` - Provides a list of all value types
    * ``target_types`` - Provides a list of all target types
    * ``condition_types`` - Provides a list of all condition types
    * ``parameter_types`` - Provides a list of all parameter types

``nglayouts.layoutTemplate``

    This variable is a shortcut to access the template name of the layout
    resolved in current request (available as ``nglayouts.layoutView.template``).
    You will mostly use this variable in your full views to extend from instead
    of your default pagelayout. Using this variable starts the layout resolving
    process if it was not ran already. In case when no layout was resolved,
    this variable holds the name of your default pagelayout, so your full views
    can fallback to it without need to modify them.

``nglayouts.pageLayoutTemplate``

    This variable holds the name of your default pagelayout which you configured
    inside Netgen Layouts. It is mostly used to extend from in frontend layout
    templates, so those templates can fallback to it to render the page head,
    header, footer and so on.
