
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})

include_directories(common server)

set(ClueLib_SRCS
	common/utility.cpp
	server/ClueAreaManager.cpp
	client/Clue.cpp
	client/InspectApplicationKitObjects.cpp
	client/InspectDeviceKitObjects.cpp
	client/InspectGameKitObjects.cpp
	client/InspectInterfaceKitObjects.cpp
	client/InspectKernelKitObjects.cpp
	client/InspectMediaKitObjects.cpp
	client/InspectMidiKitObjects.cpp
	client/InspectOther.cpp
	client/InspectStorageKitObjects.cpp
	client/InspectSupportKitObjects.cpp
	client/InspectTranslationKitObjects.cpp
	client/Inspect_Enums.cpp
	client/Inspect_Structs.cpp
	)

add_library(clue SHARED ${ClueLib_SRCS})
