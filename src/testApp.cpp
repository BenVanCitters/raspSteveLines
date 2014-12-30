#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	cout << "AudioShader" << endl;
	audioShader.load("audioShader.vert", "audioShader.frag", "");
	cout << "swirly Shader: " << endl;
	shader.load("feedback.vert", "feedback.frag", "");

	drawWidth = ofGetScreenWidth();
	drawHeight = ofGetScreenHeight();


	//allocate and clear the framebuffer
	fbo.allocate(drawWidth, drawHeight, GL_RGBA);
	fbo.begin();
		ofClear(0, 0, 0, 0);
	fbo.end();

	ofHideCursor();
	ofEnableAlphaBlending();

	fingerMovie.loadMovie("movies/fingers.mov");
	fingerMovie.play();
	fingerMovie.setLoopState(OF_LOOP_NORMAL);
	ofSetBackgroundAuto(false);

	soundSetup();
}

void testApp::soundSetup()
{
        soundStream.listDevices();

        //if you want to set a different device id
        soundStream.setDeviceID(2); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
        int bufferSize = 256;
        left.assign(bufferSize*2, 0.0);
        soundStream.setup(this, 0, 1, 44100, bufferSize, 1);
        audioSamples = new ofVec2f[bufferSize*2];
        float hSpacing =    ofGetScreenWidth() *1.f/bufferSize;;

	levels = new float[bufferSize*2];
	for(int i = 0; i < bufferSize; i++)
	{
		audioSamples[2*i] = ofVec2f(i*hSpacing, -150);
		audioSamples[2*i+1] = ofVec2f(i*hSpacing, 150);
		levels[2*i] = levels[2*i+1]= ofRandom(-100,100);
	}
	audioStrip.setVertexData(audioSamples, bufferSize*2, GL_STATIC_DRAW);
	audioAttribLocation = audioShader.getAttributeLocation("audioLevel");
	audioStrip.setAttributeData(audioAttribLocation, levels, 1,2*bufferSize, GL_DYNAMIC_DRAW);
}

testApp::~testApp()
{
	delete[] levels;
	delete[] audioSamples;
}
//--------------------------------------------------------------
void testApp::update(){
    	fingerMovie.update();
	audioStrip.updateAttributeData(audioAttribLocation, levels, 256*2);

    	//render to 'frame' or texture
	fbo.begin();
		shader.begin();
			shader.setUniform1f("time", ofGetElapsedTimef());
    			shader.setUniform2f("resolution", drawWidth, drawHeight);
    			shader.setUniformTexture("tex0", fbo.getTextureReference(), 1);
    			fbo.draw(0, 0);
    		shader.end();
		ofPushMatrix();
		ofTranslate(0,drawHeight/2);
		audioShader.begin();
			ofTexture texRef = fingerMovie.getTextureReference();
			texRef.setTextureWrap(GL_REPEAT, GL_REPEAT);
    			audioShader.setUniformTexture("tex0", texRef, 1);
    			audioShader.setUniform2f("resolution", drawWidth, drawHeight);
			audioStrip.draw(GL_TRIANGLE_STRIP, 0, 512);
    			//ofRect(0,-20, drawWidth/2,100);
    			//ofRect(50,150, drawWidth/2-50,150);
		audioShader.end();
		ofPopMatrix();
    		//fingerMovie.draw(500,300);
    	fbo.end();
}

//--------------------------------------------------------------
void testApp::draw(){
    	fbo.draw(0, 0);

	// draw the left channel:
//	ofPushStyle();
//		ofPushMatrix();
//		ofTranslate(32, 170, 0);
//
//		ofSetColor(225);
//		ofDrawBitmapString("Left Channel", 4, 18);
//
//		ofSetLineWidth(1);
//		//ofRect(0, 0, 512, 200);
//
//		ofSetColor(245, 58, 135);
//		ofSetLineWidth(3);
//		ofBeginShape();
//			for (unsigned int i = 0; i < left.size()/2; i++){
//				ofVertex(i*2, levels[i*2]*1.8f);
//			}
//		ofEndShape(false);
//		ofPopMatrix();
//	ofPopStyle();
}

//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){

//	float maxv = -1;
//	float minv = 99999;
        //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
        for (int i = 0; i < bufferSize; i++){
		//maxv = max(maxv,input[i]);
		//minv = min(minv,input[i]);
                left[2*i] = left[2*i+1]  = input[i]*1800;
		levels[2*i+1] = levels[2*i] = left[2*i];
        	//audioSamples[i] = ofVec2f(i*hSpacing, input[i]);
	}
//cout << "audio max/min:{" << maxv << "," << minv << endl;
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
}

