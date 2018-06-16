Events
======

Netgen Layouts dispatches some events in a lifecycle of displaying the page with
a resolved layout that you can listen to and act upon.

The following lists all available events.

ngbm.view.build_view
--------------------

**Event class**: ``Netgen\BlockManager\Event\CollectViewParametersEvent``

This event will be dispatched when the view of a value is being built. It can be
used to inject custom variables into the view **before** the view is built.

For example, you can use the following to inject a variable into the block view:

.. code-block:: php

    public function onBuildView(CollectViewParametersEvent $event): void
    {
        $view = $event->getView();
        if (!$view instanceof BlockViewInterface) {
            // Do nothing if the view does not belong to a block
            return;
        }

        if ($view->getContext() !== 'default') {
            // Do nothing if the view context is not for the frontend
            return;
        }

        $event->addParameter('the_answer', 42);
    }

ngbm.view.render_view
---------------------

**Event class**: ``Netgen\BlockManager\Event\CollectViewParametersEvent``

This event will be dispatched when the view of a value is being rendered. It can
be used to inject custom variables into the view **before** the view is sent to
Twig for rendering.

The example for injecting a variable into the view is the same as with
``build_view`` event.

ngbm.admin.match
----------------

**Event class**: ``Netgen\Bundle\BlockManagerAdminBundle\Event\AdminMatchEvent``

This event will be dispatched when the request is matched as being a
Netgen Layouts admin interface request. It is usually used if you want to
override the pagelayout of Netgen Layouts admin interface for integrating it in
other admin panels.
