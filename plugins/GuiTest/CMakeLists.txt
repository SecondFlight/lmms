INCLUDE(BuildPlugin)

BUILD_PLUGIN(guitest GuiTest.cpp GuiTestControls.cpp GuiTestControlDialog.cpp MOCFILES GuiTestControls.h GuiTestControlDialog.h EMBEDDED_RESOURCES artwork.png logo.png)
