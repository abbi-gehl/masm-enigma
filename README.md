# masm-enigma
This is a digital simulation of the German Enigma machine written in x64 MASM assembly and C++.

You may be asking: "Why on earth would you do this?" Good question, it is for a final project in a computer architecture class.

Authored by Abbi Gehlbach and Harrison Blair

## How to Use
Clone the repository into a visual studio workspace. Type the message you want to encrypt or decrypt into the input.txt file. Ideally, you should format your message in all CAPS and only use letters. If you include spaces in your message, they will be replaced with a 'J' character as Engima did not encode spaces. Any punctuation added will be omitted as Enigma did not use punctuation. However, you could enter a message like "Hello, please encrypt this!" and the program handles any overhead with data cleanup.

The program runs through the encryption, writes the result in output.txt, and prints it to the console. As Enigma is a symmetric encryption method, if you run an encrypted method back through the encryption algorithm, it will return the plaintext you entered. To do this just copy the message encrypted in the output file, paste it into the input file, and run the program again. With the real Enigma machine, you can change the order and position of the rotors, and use different settings for the switchboard. Figuring out these settings every day was what made Enigma so hard to crack for the Allies in WWII. More can be read about this in our write-up.

## Link to Research Proposal
> https://www.overleaf.com/read/kmtzjhjrthzq#c4e403
