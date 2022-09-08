.. note::

    If you are using Doctrine Migrations for other parts of your app and generate a new migration with
    `doctrine:migrations:diff` console command, the generated migration will now include SQL commands that drop
    Netgen Layouts tables. To prevent this from happening, you can add the following config to your Doctrine
    configuration (if you already have ``schema_filter`` config, update it accordingly):

    .. code-block:: php

        doctrine:
            dbal:
                schema_filter: ~^(?!nglayouts_)~
