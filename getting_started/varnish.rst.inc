Updates to Varnish VCL
----------------------

To enable caching and later cache clearing of block and layout HTTP caches, you
will need to use Varnish. To make the cache clearing work, you need to modify
your Varnish VCL and add the following rules somewhere in your ``vcl_recv``
function. If you're using eZ Platform and the VCL supplied by it, the best place
to put this is in ``ez_purge`` function (which is called from ``vcl_recv``),
right after ``if (req.http.X-Location-Id) { ... }`` block.

For Varnish 3:

.. code-block:: vcl

    if (req.http.X-Layout-Id) {
        ban( "obj.http.X-Layout-Id ~ " + req.http.X-Layout-Id);
        if (client.ip ~ debuggers) {
            set req.http.X-Debug = "Ban done for layout with ID " + req.http.X-Layout-Id;
        }
        error 200 "Banned";
    }

    if (req.http.X-Block-Id) {
        ban( "obj.http.X-Block-Id ~ " + req.http.X-Block-Id);
        if (client.ip ~ debuggers) {
            set req.http.X-Debug = "Ban done for block with ID " + req.http.X-Block-Id;
        }
        error 200 "Banned";
    }

For Varnish 4 and later:

.. code-block:: vcl

    if (req.http.X-Layout-Id) {
        ban("obj.http.X-Layout-Id ~ " + req.http.X-Layout-Id);
        if (client.ip ~ debuggers) {
            set req.http.X-Debug = "Ban done for layout with ID " + req.http.X-Layout-Id;
        }
        return (synth(200, "Banned"));
    }

    if (req.http.X-Block-Id) {
        ban("obj.http.X-Block-Id ~ " + req.http.X-Block-Id);
        if (client.ip ~ debuggers) {
            set req.http.X-Debug = "Ban done for block with ID " + req.http.X-Block-Id;
        }
        return (synth(200, "Banned"));
    }
