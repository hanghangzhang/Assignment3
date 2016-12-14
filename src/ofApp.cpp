#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(ofGetWidth(), ofGetHeight());//Start the video to play
}

//--------------------------------------------------------------
void ofApp::update(){
//    video.update();
    grabber.update();//Decode the new frame if needed
    //Do computing only if the new frame was obtained
    if ( grabber.isFrameNew() ) {
        //Store the previous frame, if it exists till now
        if ( grayImage.bAllocated ) {
            grayImagePrev = grayImage;
        }
        
        //Getting a new frame
        image.setFromPixels( grabber.getPixelsRef() );
        grayImage = image;	//Convert to grayscale image
        
        //Do processing if grayImagePrev is inited
        if ( grayImagePrev.bAllocated ) {
            //Get absolute difference
            diff.absDiff( grayImage, grayImagePrev );
            
                      diffFloat = diff;	//Convert to float image
            diffFloat *= 4.0;	//Amplify the pixel values
            
            //Update the accumulation buffer
            if ( !bufferFloat.bAllocated ) {
                //If the buffer is not initialized, then
                //just set it equal to diffFloat
                bufferFloat = diffFloat;
            }
            else {
                //Slow damping the buffer to zero
                bufferFloat *= 0.85;
                //Add current difference image to the buffer
                bufferFloat += diffFloat;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    float noise=ofNoise(1);

    ofBackground( 0, 255,80*noise);	//Set the background color
    
   
    if ( diffFloat.bAllocated ) {
        //Get image dimensions
        int w = grayImage.width;
        int h = grayImage.height;
        
        //Set color for images drawing
        ofSetColor(0, 255, 80*noise);
        
                  for(int i =5; i<365; i+=5){
                        ofPushMatrix();
                        ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
            
                        ofScale(0.5,0.5);
                        ofRotate(i);
//
                        bufferFloat.draw(0,0);

    }
    }
}

////--------------------------------------------------------------
//void ofApp::keyPressed(int key){
//    
//}
//
////--------------------------------------------------------------
//void ofApp::keyReleased(int key){
//    
//}
//
////--------------------------------------------------------------
//void ofApp::mouseMoved(int x, int y ){
//    
//}
//
////--------------------------------------------------------------
//void ofApp::mouseDragged(int x, int y, int button){
//    
//}
//
////--------------------------------------------------------------
//void ofApp::mousePressed(int x, int y, int button){
//    
//}
//
////--------------------------------------------------------------
//void ofApp::mouseReleased(int x, int y, int button){
//    
//}
//
////--------------------------------------------------------------
//void ofApp::windowResized(int w, int h){
//    
//}
//
////--------------------------------------------------------------
//void ofApp::gotMessage(ofMessage msg){
//    
//}
//
////--------------------------------------------------------------
//void ofApp::dragEvent(ofDragInfo dragInfo){
//    
//}
