TEMPLATE = subdirs

SUBDIRS += \
    xrpg \
    xrpg-shared

xrpg.depends = xrpg-shared
