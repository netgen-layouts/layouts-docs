Creating custom query types
===========================

When installed on pure Symfony, Netgen Layouts comes with no built in query
types which means you can only use manual collections in your blocks.

.. tip::

    If you install Netgen Layouts on eZ Platform, you will get a single query
    type that will be automatically used when switching a collection from manual
    to dynamic in blocks.

When you implement your own query types, you will be able to use dynamic
collections, and if you implement more than one query type, you will be able to
select which query type to use when switching to dynamic collection in a block.

To implement a query type, you need a bit of configuration and a PHP class that
will handle custom functionalities of a query type. In the following examples,
we will show creating a custom query type that will use eZ search engine to
search for items by text.

Configuring a new query type
----------------------------

To register a new query type in Netgen Layouts, you will need the following
configuration:

.. code-block:: yaml

    netgen_block_manager:
        query_types:
            my_search:
                name: 'My search'

This configuration specifies a new query type with ``my_search`` identifier and
``My search`` human readable name.

Creating a PHP service for a query type
---------------------------------------

Every query type needs a single PHP class that specifies the entire behaviour of
a query type. This class needs to implement
``Netgen\BlockManager\Collection\QueryType\QueryTypeHandlerInterface`` interface
which specifies a number of methods for you to implement.

Let's create a basic query type handler class:

.. code-block:: php

    <?php

    namespace AppBundle\Collection\QueryType\Handler;

    use Netgen\BlockManager\API\Values\Collection\Query;
    use Netgen\BlockManager\Collection\QueryType\QueryTypeHandlerInterface;
    use Netgen\BlockManager\Parameters\ParameterBuilderInterface;

    class MySearchHandler implements QueryTypeHandlerInterface
    {
        /**
         * Builds the parameters by using provided parameter builder.
         *
         * @param \Netgen\BlockManager\Parameters\ParameterBuilderInterface $builder
         */
        public function buildParameters(ParameterBuilderInterface $builder)
        {
        }

        /**
         * Returns the values from the query.
         *
         * @param \Netgen\BlockManager\API\Values\Collection\Query $query
         * @param int $offset
         * @param int $limit
         *
         * @return mixed[]
         */
        public function getValues(Query $query, $offset = 0, $limit = null)
        {
        }

        /**
         * Returns the value count from the query.
         *
         * @param \Netgen\BlockManager\API\Values\Collection\Query $query
         *
         * @return int
         */
        public function getCount(Query $query)
        {
        }

        /**
         * Returns if the provided query is dependent on a context, i.e. currently displayed page.
         *
         * @param \Netgen\BlockManager\API\Values\Collection\Query $query
         *
         * @return bool
         */
        public function isContextual(Query $query)
        {
        }
    }

Specifying query type parameters
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

First method we will look at is ``buildParameters`` method. By using an object
called parameter builder and adding parameter specifications to it, this method
will specify which parameters your custom query type will have. Details on how
the parameter builder works, what parameter types exist and how to implement
custom parameter type are explained in dedicated chapter.

Let's add a custom parameter to our query type which will serve as an input for
search text:

.. code-block:: php

    use Netgen\BlockManager\Parameters\ParameterType;

    public function buildParameters(ParameterBuilderInterface $builder)
    {
        $builder->add('search_text', ParameterType\TextType::class);
    }

Notice that we didn't specify the human readable label for the parameter.
That's because it is generated automatically via translation system. To
create the correct labels for your query type parameters, you need to add one
string to ``ngbm`` translation catalog for every parameter in your query type
with the format ``query.<query_type>.<parameter_name>`` where ``query_type`` and
``parameter_name`` are placeholders that need to be replaced with correct values.

So, for our custom search query type, the translation file would look something
like this:

.. code-block:: yaml

    query.my_search.search_text: 'Search text'

Fetching the items
~~~~~~~~~~~~~~~~~~

Second method in our handler example above is called ``getValues``. This method
is used for fetching the items from a query.

This method needs to return the array of domain objects that will be
automatically converted to block items.

.. tip::

    In case of eZ Platform, query types can return the list of eZ ``ContentInfo``
    or ``Location`` objects.

.. code-block:: php

    /**
     * @var \eZ\Publish\API\Repository\SearchService
     */
    protected $searchService;

    public function __construct(SearchService $searchService)
    {
        $this->searchService = $searchService;
    }

    public function getValues(Query $query, $offset = 0, $limit = null)
    {
        $searchResult = $this->searchService->findLocations(
            $this->buildQuery($query, $offset, $limit)
        );

        return array_map(
            function (SearchHit $searchHit) {
                return $searchHit->valueObject;
            },
            $searchResult->searchHits
        );
    }

    /**
     * Builds the query from current parameters.
     *
     * @param \Netgen\BlockManager\API\Values\Collection\Query $query
     * @param bool $buildCountQuery
     * @param int $offset
     * @param int $limit
     *
     * @return \eZ\Publish\API\Repository\Values\Content\LocationQuery
     */
    protected function buildQuery(Query $query, $buildCountQuery = false, $offset = 0, $limit = null)
    {
        $locationQuery = new LocationQuery();

        $criteria = array(
            new Criterion\FullText($query->getParameter('search_text')->getValue()),
            new Criterion\Visibility(Criterion\Visibility::VISIBLE),
        );

        $locationQuery->filter = new Criterion\LogicalAnd($criteria);

        $locationQuery->limit = 0;
        if (!$buildCountQuery) {
            $locationQuery->offset = $offset;
            $locationQuery->limit = $limit;
        }

        return $locationQuery;
    }

As you can see, ``getValues`` method simply builds a location query for eZ
search engine and returns the list of found eZ locations. Conversion to block
items is handled automatically by Netgen Layouts.

Fetching the item count
~~~~~~~~~~~~~~~~~~~~~~~

To retrieve the item count from the query type, we use the ``getCount`` method:

.. code-block:: php

    public function getCount(Query $query)
    {
        $searchResult = $this->searchService->findLocations(
            $this->buildQuery($query, true)
        );

        return $searchResult->totalCount;
    }

Contextual queries
~~~~~~~~~~~~~~~~~~

A contextual query is a query which needs the current context (i.e. current
page) to run. Think of a situation where you have a layout with a block which
shows top 5 items from the category it is applied to. Contextual query removes
the need to create five different layouts for five different categories just so
you can change the parent category from which to fetch the items. Instead, in a
contextual query, you will take the currently displayed category and use it as
the parent, making it possible to have only one layout for all five different
categories.

In order for the system to work properly with contextual queries, one method is
used, ``isContextual``, which signals to the system if the query is contextual
or not. Most of the time, this method will return a value of a boolean parameter
specified inside of the query which decides if a query is contextual or not, for
example:

  .. code-block:: php

      public function isContextual(Query $query)
      {
          return $query->getParameter('use_current_location')->getValue() === true;
      }

In our case, we will simply return ``false`` from ``isContextual`` method:

.. code-block:: php

    public function isContextual(Query $query)
    {
        return false;
    }

Defining the Symfony service for our handler
--------------------------------------------

To connect the created handler with query type configuration, we need to
register the handler in Symfony DIC:

.. code-block:: yaml

    services:
        app.collection.query_type.handler.my_search:
            class: AppBundle\Collection\QueryType\Handler\MySearchHandler
            arguments:
                - "@ezpublish.api.service.search"
            tags:
                - { name: netgen_block_manager.collection.query_type_handler, type: my_search }

This configuration is a fairly regular specification of services in Symfony,
however, to correctly recognize our PHP class as a query type handler, we need
to tag it with ``netgen_block_manager.collection.query_type_handler`` tag and
attach to it an ``type`` key with a value which equals to the identifier of
query type we configured at the beginning (in this case ``my_search``).

After this, our query type is ready for usage.
