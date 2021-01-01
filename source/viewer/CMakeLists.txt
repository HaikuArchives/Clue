
include_directories(../library/server)

set(Clue_Viewer_SOURCES
	ActiveMenuItem.cpp
	AnimatedView.cpp
	BackView.cpp
	BetterScrollView.cpp
	BitmapButton.cpp
	BitmapMenuItem.cpp
	ClueFact.cpp
	ClueItem.cpp
	ClueTabView.cpp
	CLVColumn.cpp
	CLVColumnLabelView.cpp
	CLVListItem.cpp
	ColumnListView.cpp
	constants.cpp
	CreditsView.cpp
	CTeamListView.cpp
	DragMessageItem.cpp
	DragMessageView.cpp
	DragMessageWindow.cpp
	EditBoolView.cpp
	EditColorView.cpp
	EditTeamView.cpp
	EditView.cpp
	FingerprintCLV.cpp
	FingerprintZoomView.cpp
	FingerprintZoomWnd.cpp
	ListCountStringView.cpp
	LiveView.cpp
	main.cpp
	MainWindow.cpp
	ObjectFilterItem.cpp
	ObjectFilterView.cpp
	ObjectFilterWnd.cpp
	PreferenceItem.cpp
	PreferencesView.cpp
	PreferencesWnd.cpp
	PrintView.cpp
	PrintWindow.cpp
	PropertyItem.cpp
	RefFilter.cpp
	Reporter.cpp
	SettingsManager.cpp
	Slider.cpp
	SplashView.cpp
	SplashWindow.cpp
	SplitterView.cpp
	StatusBarView.cpp
	TeamCLV.cpp
	TeamItem.cpp
	TeamPropertyView.cpp
	TeamPropertyWindow.cpp
	TeamTab.cpp
	TheApp.cpp
	ToolTipView.cpp
	ToolTipWindow.cpp
	Utility.cpp
	Clue.rdef
	)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_executable(ClueViewer ${Clue_Viewer_SOURCES})

target_link_libraries(ClueViewer "be" "tracker" "stdc++" "clue")
