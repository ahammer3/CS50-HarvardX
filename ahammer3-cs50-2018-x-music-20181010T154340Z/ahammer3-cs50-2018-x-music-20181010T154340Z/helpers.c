// Helper functions for music

#include <cs50.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO
    //fraction string will be read in as X/Y. Can check X by fraction[0] and Y by fraction[2]
    //If numerator is 1 -> simplest form
    if (fraction[0] == '1')
    {
        if (fraction[2] == '1')
        {
            return 8;
        }
        else if (fraction[2] == '2')
        {
            return 4;
        }
        //There are no 3s, 5s, etc in this position because we assume a power of 2 for denominator
        else if (fraction[2] == '4')
        {
            return 2;
        }
        else if (fraction[2] == '8')
        {
            return 1;
        }
    }
    //numerator can't really be 2,4,5, etc. because it can be reduced anyway. 3 is a 3/8 possibility
    else if (fraction[0] == '3')
    {
        if (fraction[2] == '8')
        {
            return 3;
        }
    }
    //return 0 if nothing matches
    else
    {
        return 0;
    }
    //return 0 if none of these match at all in the first place
    return 0;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // TODO
    //the note is passed in through string - note will be note[0]
    //octave will be the end char of note (length)
    int octave = note[strlen(note) - 1];
    //adjust the char rep ascii
    octave = octave - 48;

    //declare frequency
    double frequency = 0.0;

    //note letter cases - adjust one step at a time from A, A being 440 default
    switch (note[0])
    {
        case 'C' :
            frequency = 440.0 / (pow(2.0, (9.0 / 12.0)));
            break;

        case 'D' :
            frequency = 440.0 / (pow(2.0, (7.0 / 12.0)));
            break;

        case 'E' :
            frequency = 440.0 / (pow(2.0, (5.0 / 12.0)));
            break;

        case 'F' :
            frequency = 440.0 / (pow(2.0, (4.0 / 12.0)));
            break;

        case 'G' :
            frequency = 440.0 / (pow(2.0, (2.0 / 12.0)));
            break;

        case 'A' :
            frequency = 440.0;
            break;

        case 'B' :
            frequency = 440.0 * (pow(2.0, (2.0 / 12.0)));
            break;

        //unknown letter - error
        default :
            return 0;
    }

    //next we account for octave
    int octaveShift;

    octaveShift = octave - 4;

    //higher than 4 octave
    if (octaveShift > 0)
    {
        frequency = frequency * (2 * octaveShift);
    }
    //lower than 4 octave - else frequency stays the same
    else if (octaveShift < 0)
    {
        //adjust octaveShift
        octaveShift = octaveShift * (-1);
        frequency = frequency / (2 * octaveShift);
    }

    //next adjust for flats and sharps
    if (note[1] == 'b')
    {
        frequency /= (pow(2.0, (1.0 / 12.0)));
    }
    else if (note[1] == '#')
    {
        frequency *= (pow(2.0, (1.0 / 12.0)));
    }

    //finally convert double to int (round)
    int returnFrequency;

    returnFrequency = round(frequency);

    return returnFrequency;

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // TODO
    //If s is a rest -> True, else False
    //compare string s with "" using strncmp
    if (strncmp(s, "", 1))
    {
        return false;
    }
    else
    {
        return true;
    }

}
