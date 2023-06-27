#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(3);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 50, true, true, true);
	//this->word = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	this->word = "0123456789";
}

//--------------------------------------------------------------
void ofApp::update() {


}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofColor color;
	ofSeedRandom(39);
	for (int i = 0; i < 600; i++) {

		auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
		auto location = glm::vec2(
			ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * 0.0025), 0, 1, -600, 600),
			ofMap(ofNoise(noise_seed.y, ofGetFrameNum() * 0.0025), 0, 1, -600, 600));
		auto next = glm::vec2(
			ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + 1) * 0.0025), 0, 1, -600, 600),
			ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + 1) * 0.0025), 0, 1, -600, 600));
		auto angle = std::atan2(next.y - location.y, next.x - location.x);


		ofPushMatrix();
		ofTranslate(location);
		ofRotate(angle * RAD_TO_DEG + 90);

		ofPath chara_path = this->font.getCharacterAsPoints(this->word[(int)ofRandom(this->word.size())], true, false);
		vector<ofPolyline> outline = chara_path.getOutline();

		ofFill();
		ofSetColor(ofMap(i, 0, 600, 39, 239));
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			ofNextContour(true);

			auto vertices = outline[outline_index].getVertices();
			for (auto& vertex : vertices) {

				ofVertex(vertex);
			}
		}
		ofEndShape(true);

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}