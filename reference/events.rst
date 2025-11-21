Events
======

Netgen Layouts dispatches some events in a lifecycle of displaying the page with
a resolved layout that you can listen to and act upon.

The following lists all available events.

``Netgen\Layouts\Event\BuildViewEvent``
---------------------------------------

This event will be dispatched when the view of a value is being built. It can be
used to inject custom variables into the view **before** the view is built.

For example, you can use the following to inject a variable into the block view:

.. code-block:: php

    public function onBuildView(BuildViewEvent $event): void
    {
        if (!$event->view instanceof BlockViewInterface) {
            // Do nothing if the view does not belong to a block
            return;
        }

        if ($event->view->context !== 'default') {
            // Do nothing if the view context is not for the frontend
            return;
        }

        $event->view->addParameter('the_answer', 42);
    }

``Netgen\Layouts\Event\RenderViewEvent``
----------------------------------------

This event will be dispatched when the view of a value is being rendered. It can
be used to inject custom variables into the view **before** the view is sent to
Twig for rendering.

The example for injecting a variable into the view is the same as with
``BuildViewEvent`` event.

``Netgen\Bundle\LayoutsAdminBundle\Event\AdminMatchEvent``
----------------------------------------------------------

This event will be dispatched when the request is matched as being a
Netgen Layouts admin interface request. It is usually used if you want to
override the pagelayout of Netgen Layouts admin interface for integrating it in
other admin panels.
