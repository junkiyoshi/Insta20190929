#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetColor(39);
	ofSetLineWidth(3);
	ofNoFill();
	ofEnableDepthTest();

	this->font_size = 80;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	vector<char> charactors = {
		'1', '2', '3', '4', '5',
		'6', '7', '8', '9', '1'
		 };

	for (int i = 0; i < 4; i += 1) {

		ofRotateY(90);
		for (int x = -120; x < 120; x += this->font_size) {

			for (int y = -480; y < 480; y += this->font_size) {

				auto location = glm::vec3(x, y, 120);
				float angle = PI * 0.5 * i;
				auto rotation = glm::rotate(glm::mat4(), angle, glm::vec3(0, 1, 0));
				auto noise_location = glm::vec4(location, 0) * rotation;

				int charactor_index = ofMap(ofNoise(noise_location.x * 0.001, noise_location.y * 0.001 + ofGetFrameNum() * 0.01, noise_location.z * 0.001), 0, 1, 0, charactors.size());
				auto path = this->font.getCharacterAsPoints(charactors[charactor_index], true, false);
				auto outline = path.getOutline();

				ofPushMatrix();
				ofTranslate(location);

				ofFill();
				ofSetColor(239);
				ofBeginShape();
				for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

					if (outline_index != 0) { ofNextContour(true); }

					auto vertices = outline[outline_index].getVertices();
					for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

						auto location = glm::vec2(this->font_size - vertices[vertices_index].x, vertices[vertices_index].y + this->font.stringHeight(string{ charactors[i] }) * 0.5);
						ofVertex(location);
					}
				}
				ofEndShape(true);

				ofNoFill();
				ofSetColor(39);
				ofBeginShape();
				for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

					if (outline_index != 0) { ofNextContour(true); }

					auto vertices = outline[outline_index].getVertices();
					for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

						auto location = glm::vec2(this->font_size - vertices[vertices_index].x, vertices[vertices_index].y + this->font.stringHeight(string{ charactors[i] }) * 0.5);
						ofVertex(location);
					}
				}
				ofEndShape(true);

				ofPopMatrix();
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}