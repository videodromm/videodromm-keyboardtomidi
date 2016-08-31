#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

// Settings
#include "VDSettings.h"
// Session
#include "VDSession.h"
// Animation
#include "VDAnimation.h"
// Log
#include "VDLog.h"
// Utils
#include "VDUtils.h"
// Message router
#include "VDRouter.h"
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
	// Log
	VDLogRef					mVDLog;
	// Animation
	VDAnimationRef				mVDAnimation;
	// Utils
	VDUtilsRef					mVDUtils;
	// Message router
	VDRouterRef					mVDRouter;
	// UI
	VDUIRef						mVDUI;
	// Mix
	VDMixList					mMixes;
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
	// Utils
	mVDUtils = VDUtils::create(mVDSettings);
	// Animation
	mVDAnimation = VDAnimation::create(mVDSettings, mVDSession);
	// Message router
	mVDRouter = VDRouter::create(mVDSettings, mVDAnimation, mVDSession);
	// Mix
	mMixesFilepath = getAssetPath("") / mVDSettings->mAssetsPath / "mixes.xml";
	if (fs::exists(mMixesFilepath)) {
		// load textures from file if one exists
		mMixes = VDMix::readSettings(mVDSettings, mVDAnimation, mVDRouter, loadFile(mMixesFilepath));
	}
	else {
		// otherwise create a texture from scratch
		mMixes.push_back(VDMix::create(mVDSettings, mVDAnimation, mVDRouter));
	}
	mVDAnimation->tapTempo();
	// UI
	mVDUI = VDUI::create(mVDSettings, mMixes[0], mVDRouter, mVDAnimation, mVDSession);

	mColor = ColorA(0.5f, 0.0f, 0.2f, 1.0f);
}
void KeyboardToMidiApp::keyDown(KeyEvent event)
{
	CI_LOG_V((int)event.getCode());

	// Animation did not handle the key, so handle it here
	switch (event.getCode()) {
	case KeyEvent::KEY_ESCAPE:
		// quit the application
		quit();
		break;
	case KeyEvent::KEY_UP:
		// vert
		mColor = ColorA(0.0f, 1.0f, 0.0f, 1.0f);
		mVDRouter->midiOutSendNoteOn(1, 1, 40, 64);
		//mVDRouter->
		break;
	case KeyEvent::KEY_KP6:
		// jaune
		mColor = ColorA(1.0f, 1.0f, 0.0f, 1.0f);
		mVDRouter->midiOutSendNoteOn(1, 1, 42, 64);
		break;
	case KeyEvent::KEY_RETURN:
		// rouge
		mColor = ColorA(1.0f, 0.0f, 0.0f, 1.0f);
		mVDRouter->midiOutSendNoteOn(1, 1, 43, 64);
		break;
	case KeyEvent::KEY_KP2:
		// bleu
		mColor = ColorA(0.0f, 0.0f, 1.0f, 1.0f);
		mVDRouter->midiOutSendNoteOn(1, 1, 45, 64);
		break;
	case KeyEvent::KEY_DELETE:
		// blanc
		mColor = ColorA(1.0f, 1.0f, 1.0f, 1.0f);
		mVDRouter->midiOutSendNoteOn(1, 1, 47, 64);
		break;
	}

}
void KeyboardToMidiApp::keyUp(KeyEvent event)
{
	if (!mVDAnimation->handleKeyUp(event)) {
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
