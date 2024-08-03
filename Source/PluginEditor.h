/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "JSMidiKeyboardComponent.h"


class KeyboardStateListener : public juce::MidiKeyboardState::Listener, public juce::ChangeBroadcaster {
public:
    std::vector<int> activeNotes;

    void handleNoteOn(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override {
        activeNotes.push_back(midiNoteNumber);
        sendChangeMessage();
    }

    void handleNoteOff(MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override {
        for (auto it = activeNotes.begin(); it != activeNotes.end(); ++it) {
            if (*it == midiNoteNumber) {
                activeNotes.erase(it);
                break;
            }
        }
        sendChangeMessage();
    }
};

//==============================================================================
/**
*/
class JohnSlapAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::ChangeListener
{
public:
    JohnSlapAudioProcessorEditor (JohnSlapAudioProcessor&);
    ~JohnSlapAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void changeListenerCallback(juce::ChangeBroadcaster* source);

    JSMidiKeyboardComponent kbComponent;

    static const juce::Font getHelvetica()
    {
        static juce::Font typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::Helvetica_ttf, BinaryData::Helvetica_ttfSize);
        return typeface;
    }

    static const juce::Font getHelveticaLight()
    {
        static juce::Font typeface = juce::Typeface::createSystemTypefaceFor(BinaryData::HelveticaLight_ttf, BinaryData::HelveticaLight_ttfSize);
        return typeface;
    }

    KeyboardStateListener kbListener;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JohnSlapAudioProcessor& audioProcessor;

    int HEIGHT = 400;
    int WIDTH = 800;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JohnSlapAudioProcessorEditor)
};