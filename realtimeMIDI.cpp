
#include <iostream>
#include <cstdlib>
#include <RtMidi.h>

// Callback function to handle incoming MIDI messages
void midiCallback(double deltatime, std::vector<unsigned char>* message, void* userData) {
    unsigned int nBytes = message->size();
    for (unsigned int i = 0; i < nBytes; i++) {
        std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
    }
    if (nBytes > 0)
        std::cout << "stamp = " << deltatime << std::endl;
}

int main() {
    RtMidiIn* midiin = nullptr;

    // Create an RtMidiIn instance
    try {
        midiin = new RtMidiIn();
    }
    catch (RtMidiError& error) {
        error.printMessage();
        exit(EXIT_FAILURE);
    }

    // Check available ports
    unsigned int nPorts = midiin->getPortCount();
    if (nPorts == 0) {
        std::cout << "No MIDI input ports available!" << std::endl;
        delete midiin;
        return 0;
    }

    // Open the first available port
    midiin->openPort(0);

    // Set the callback function
    midiin->setCallback(&midiCallback);

    // Don't ignore sysex, timing, or active sensing messages
    midiin->ignoreTypes(false, false, false);

    // Wait for input
    std::cout << "Reading MIDI input ... press <enter> to quit." << std::endl;
    char input;
    std::cin.get(input);

    // Clean up
    delete midiin;

    return 0;
}
