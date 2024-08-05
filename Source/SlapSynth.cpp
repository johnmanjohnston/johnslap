/*
  ==============================================================================

    SlapSynth.cpp
    Created: 28 Jul 2024 3:59:09pm
    Author:  USER

  ==============================================================================
*/

#include "SlapSynth.h"

void SlapSynth::setup()
{
    addVoice(new juce::SamplerVoice());
    addVoice(new juce::SamplerVoice());
    addVoice(new juce::SamplerVoice());
    addVoice(new juce::SamplerVoice());
    addVoice(new juce::SamplerVoice());

    afm.registerBasicFormats();
    noteRange.setRange(0, 128, true);

    juce::File* file = new juce::File("C:\\Users\\USER\\OneDrive\\Documents\\Ableton\\Live Recordings\\2024-03-09 130654 Temp Project\\Samples\\Processed\\Consolidate\\GrandPiano C3 f [2024-03-09 130834].wav");
    juce::ScopedPointer<juce::AudioFormatReader> reader = afm.createReaderFor(*file);

    addSound(new juce::SamplerSound("default", *reader, noteRange, 69, 0.f, 0.2f, 2.f));
}

void SlapSynth::updateSampleSource(juce::MidiBuffer& midiMessages)
{
    if (midiMessages.isEmpty()) return;

    for (const auto midiData : midiMessages) {
        const auto msg = midiData.getMessage();
        const auto noteNumber = msg.getNoteNumber(); 
        const auto noteName = msg.getMidiNoteName(noteNumber, false, true, 3);

        // TODO: update sample source based on noteName
        DBG(noteName);


        juce::String fpath = "C:\\Users\\USER\\other-nerd-stuff\\projects\\JohnSlap\\samples\\trbx174\\";
        fpath.append(noteName, 3);
        fpath.append(".wav", 4);

        juce::File* file = new juce::File(fpath);

        if (file->exists()) 
        {
            removeSound(0);
            juce::ScopedPointer<juce::AudioFormatReader> reader = afm.createReaderFor(*file);
            addSound(new juce::SamplerSound("default", *reader, noteRange, noteNumber, 0.f, 0.02f, 2.f));
        }

        else { DBG(fpath + " does not exist"); }

        file = nullptr;
    }
}