message("Copying assets")
message("From ${XRPG_ASSETS_SOURCE_DIR} to ${XRPG_ASSETS_BINARY_DIR}")
file(COPY ${XRPG_ASSETS_SOURCE_DIR} DESTINATION ${XRPG_ASSETS_BINARY_DIR})
message("Assets copied")
