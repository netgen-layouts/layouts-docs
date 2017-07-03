``form_view``
=============

This view is used to render entities implementing
``Symfony\Component\Form\FormView`` interface.

Available variables
-------------------

+----------------+-----------------------------------------------------------+
| Variable name  | Description                                               |
+================+===========================================================+
| ``form``       | The Symfony form view which is being rendered             |
+----------------+-----------------------------------------------------------+
| ``formObject`` | The underlying Symfony form from which the view was built |
+----------------+-----------------------------------------------------------+
