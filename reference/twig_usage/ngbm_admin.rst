``ngbm_admin``
==============

This global variable is used by the administration interface of Netgen Layouts.
Currently, only one variable is available:

``ngbm_admin.pageLayoutTemplate``

    This variable holds the name of the pagelayout template for the admin
    interface. The idea behind it is that you can change the pagelayout of the
    administration interface without having to change the administration
    templates themselves. This can be achieved by setting this variable to a
    desired template name before admin interface is rendered (e.g. in an event
    listener).
