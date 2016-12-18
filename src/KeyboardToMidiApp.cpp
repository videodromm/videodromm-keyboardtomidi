#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

// Settings
#include "VDSettings.h"
// Session
#include "VDSession.h"
// UserInterface
#include "CinderImGui.h"
// UI
#include "VDUI.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace VideoDromm;

class KeyboardToMidiApp : public App {

public:
	static void prepare(Settings *settings);
	void						setup() override;
	void						mouseDown(MouseEvent event) override;
	void						mouseDrag(MouseEvent event) override;
	void						keyDown(KeyEvent event) override;
	void						keyUp(KeyEvent event) override;
	void						update() override;
	void						draw() override;
	void						resize() override;
	void						fileDrop(FileDropEvent event) override;
	void						cleanup() override;
private:
	// Settings
	VDSettingsRef				mVDSettings;
	// Session
	VDSessionRef				mVDSession;
	// UI
	VDUIRef						mVDUI;
	fs::path					mMixesFilepath;

	ColorA						mColor;
};

void KeyboardToMidiApp::prepare(Settings *settings)
{
	settings->setWindowSize(1024, 768);
}
void KeyboardToMidiApp::setup()
{
	// Settings
	mVDSettings = VDSettings::create();
	// Session
	mVDSession = VDSession::create(mVDSettings);
	// UI
	mVDUI = VDUI::create(mVDSettings, mVDSession);

	mColor = ColorA(0.5f, 0.0f, 0.2f, 1.0f);
}
void KeyboardToMidiApp::keyDown(KeyEvent event)
{
	CI_LOG_V((int)event.getCode());
	mVDSettings->mMsg = toString((int)event.getCode());
	// Animation did not handle the key, so handle it here
	switch (event.getCode()) {
	case 0:
		//vert
		mColor = ColorA(0.0f, 0.5f, 0.0f, 1.0f);
		mVDSession->midiOutSendNoteOn(1, 1, 46, 64);
		break;
	case 106:
		//blanc
		mColor = ColorA(0.0f, 0.0f, 0.0f, 1.0f);
		mVDSession->midiOutSendNoteOn(1, 1, 45, 64);
		break;
	case KeyEvent::KEY_ESCAPE:
		// quit the application
		quit();
		break;
	case 273:
		// bleu
		mColor = ColorA(0.0f, 1.0f, 0.0f, 1.0f);
		mVDSession->midiOutSendNoteOn(1, 1, 44, 64);
		//mVDRouter->
		break;
	case 260:
		// jaune
		mColor = ColorA(1.0f, 1.0f, 0.0f, 1.0f);
		mVDSession->midiOutSendNoteOn(1, 1, 42, 64);
		break;
	case 53:
		// petit vert
		mColor = ColorA(0.0f, 1.0f, 0.0f, 1.0f);
		mVDSession->midiOutSendNoteOn(1, 1, 48, 64);
		break;
	case 120:
		// vert2
		mColor = ColorA(1.0f, 0.0f, 0.0f, 1.0f);
		mVDSession->midiOutSendNoteOn(1, 1, 41, 64);
		break;
	case 57:
		// rouge
		mColor = ColorA(0.0f, 0.0f, 1.0f, 1.0f);
		mVDSession->midiOutSendNoteOn(1, 1, 40, 64);
		break;
	}

}
void KeyboardToMidiApp::keyUp(KeyEvent event)
{
	if (!mVDSession->handleKeyUp(event)) {
		// Animation did not handle the key, so handle it here
	}
}
void KeyboardToMidiApp::resize()
{
	mVDUI->resize();
}
void KeyboardToMidiApp::fileDrop(FileDropEvent event)
{


}
void KeyboardToMidiApp::update()
{

}
void KeyboardToMidiApp::cleanup()
{

	quit();
}
void KeyboardToMidiApp::mouseDown(MouseEvent event)
{

}
void KeyboardToMidiApp::mouseDrag(MouseEvent event)
{

}

void KeyboardToMidiApp::draw()
{

	gl::clear(mColor);
	//if (mVDUI->isReady()) {
		mVDUI->Run("UI", (int)getAverageFps());
	//}
}


CINDER_APP(KeyboardToMidiApp, RendererGl, &KeyboardToMidiApp::prepare)
