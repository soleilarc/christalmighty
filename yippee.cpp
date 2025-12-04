// compile with ( g++ -std=c++17 note_manager.cpp -o note_manager.exe ) if you dare
// mingw hates me and god looks down on me in disdain.

// i tried. i checked this over so many times. if i boned something and it doesn't compile
// for w/e reason then i'll cry lmao

// i don't plan to present this? my social anxiety is bad for this type of thing.
// and i don't have a webcam
// no seriously none of my laptops have a working webcam and my desktop just. is a desktop.
// i'd record it if i could. i have comments everywhere, i hope that's worth something?

// idk i can't actually prove it isn't ai generated hot garbage. i worked on this for... 5 ish days? off and on?
// i did have to look up a lot of this. i tried to note what i did and didn't research for but like
// no promises??? if something's weird and i don't note it then you can lmk? and i'll elaborate

// i have been WAY too swamped with math homework (my 77.13 in that class omg, plane trig is hell) & speech stuff
// i had to give a presentation on ~leadership theories~ on wednesday (day before this submission) ughhhhhhhhh
// did i tell you i have social anxiety and therefore hate presentations
// that sucked.

// (old macdonald had a farm) i'm so stressed that sunlight hurts:
// (eieio) i am god's mistake.

// in swedish because i'm learning swedish.

// jag är så stressad att solen gör ont:
// jag är guds misstag.

#include <iostream> // mmm c me out baby
#include <filesystem> // for checking folders + reading directory contents
#include <fstream> // for actually reading/writing files
#include <string> // i hate that you're a separate thing. i hate that i need you for string variables.
#include <vector>
#include <algorithm>
using namespace std; // i like namespace, bite me

const string NOTES_DIR = "notes"; // folder to store everything

// makes sure notes/ exists, nearly forgot to do this lmao
// look if you must know i did look this one up
// never done this before
void makeNotesDirectory() {
    if (!std::filesystem::exists(NOTES_DIR)) {          // check if folder exists (if NOT exists, then:)
        std::filesystem::create_directory(NOTES_DIR);   // make folder if not. never assume
        cout << "[Created notes folder.]\n";
    }
}

// returns a vector containing all the note filenames
vector<string> getNotes() {
    vector<string> list;

    // loop through everything inside notes/
    std::filesystem::directory_iterator end_iter;
    for (std::filesystem::directory_iterator entry(NOTES_DIR); entry != end_iter; ++entry) {
        // only keep .txt files and nothing else
        if (entry->is_regular_file() && entry->path().extension() == ".txt") {
            list.push_back(entry->path().filename().string());
        }
    }

    return list; // i could sort this. but i don't want to. // i do not want to. //
}

// prints the list of existing notes
void showNotes() {
    vector<string> notes = getNotes();

    if (notes.size() == 0) {
        cout << "\nNo notes found.\n"; // because obviously. there's nothing there. 0 = 0.
        return;
    }

    cout << "\nNotes:\n";
    for (int i = 0; i < notes.size(); i++) { // FOR (INT I). sorry these are my favorite for no good reason
        cout << i + 1 << ". " << notes[i] << endl; // mmm counting
    }
}

// create a new .txt file and write content to it
void createNote() {
    cout << "\nEnter a title for the note (no spaces): ";
    string title;
    cin >> title;  // reading only until the first space. god created me to be lazy-ish.

    string filename = NOTES_DIR;
    filename = filename + "/";
    filename = filename + title;
    filename = filename + ".txt";

    if (std::filesystem::exists(filename)) { // don’t. overwrite people's notes??
        cout << "That note already exists.\n";
        return;
    }

    cout << "Enter note content. '.' ends the note.\n";

    ofstream file(filename); // opens file for writing
    string line;
    bool done = false;
    while (!done) {
        getline(cin, line);
        if (line == ".") done = true;
        else file << line << "\n";
    }

    cout << "Note saved.\n";
}

// open a note and display the contents
void readNote() {
    showNotes();
    vector<string> notes = getNotes();

    if (notes.size() == 0) return;

    cout << "\nWhich note number do you want to read?: ";
    int choice;
    cin >> choice;

    if (choice < 1 || choice > notes.size()) { // exception handling, essentially
        cout << "Invalid option.\n";
        return;
    }

    string filepath = NOTES_DIR + "/" + notes[choice - 1];
    ifstream file(filepath); // open file for reading

    if (!file) { // did it open tho?
        cout << "Couldn't open the note.\n"; // if this runs, then no lol
        return;
    }

    cout << "\n--- " << notes[choice - 1] << " ---\n";

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
}

// i got mac and cheese. it's 10:34pm on tuesday night. i thought you should know this.
// it's rly good i salted it lmao
// look ok it's my end of semester project and i'm losing sanity
// i'm allowed to be funny
// i promise these comments aren't padding i'll make a rough count w/o them for you @ the end (did it! :D)

// rewrites the entire file with new content
void editNote() {
    showNotes();
    vector<string> notes = getNotes();

    if (notes.size() == 0) return;

    cout << "\nWhich note number do you want to edit?: ";
    int choice;
    cin >> choice;

    if (choice < 1 || choice > notes.size()) {
        cout << "Invalid option.\n";
        return;
    }

    string filepath = NOTES_DIR + "/" + notes[choice - 1];

    // show old content, helpful
    cout << "\nCurrent content:\n\n";
    ifstream oldFile(filepath); // just. read old content.
    string line;
    while (getline(oldFile, line)) { // line by line stuff. ez pz
        cout << line << endl;
    }

    cout << "\nEnter your new content. '.' (period) ends.\n";

    ofstream newFile(filepath);
    bool done = false;
    while (!done) {
        getline(cin, line); // spaces.
        if (line == ".") done = true;
        else newFile << line << "\n";
    }

    cout << "Note updated.\n";
}

// deletes the note file entirely
void deleteNote() {
    showNotes();
    vector<string> notes = getNotes();

    if (notes.size() == 0) return;

    cout << "\nWhich note number do you want to delete?: ";
    int choice;
    cin >> choice;

    if (choice < 1 || choice > notes.size()) { // :/
        cout << "Invalid option.\n";
        return;
    }

    cout << "Are you sure? (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') { // never assume they'll just use lowercase y. NEVER
        string filepath = NOTES_DIR + "/" + notes[choice - 1];
        std::filesystem::remove(filepath); // thanos it (i was. watching infinity war. leave me alone)
        cout << "Deleted.\n";
    } else {
        cout << "Cancelled.\n";
    }
}

// searches filenames + contents for a keyword (i thought it would be cool!!)
void searchNotes() {
    cout << "\nEnter keyword to search: ";
    string word;
    cin >> word;

    vector<string> notes = getNotes();
    vector<string> results; // store matches here

    for (int i = 0; i < notes.size(); i++) {
        bool match = false;

        // first check the filename
        if (notes[i].find(word) != string::npos) { // npos is weird. stackoverflow my beloved.
            match = true;
        }

        ifstream file(NOTES_DIR + "/" + notes[i]);
        string line;
        while (!match && getline(file, line)) { // if no match, stop reading. 
            if (line.find(word) != string::npos) {
                match = true;
            }
        }

        if (match) results.push_back(notes[i]); // stores matching note
    }

    if (results.size() == 0) {
        cout << "No matches.\n";
    } else {
        cout << "\nResults:\n";
        for (int i = 0; i < results.size(); i++) {
            cout << "- " << results[i] << endl;
        }
    }
}

// mmmm menu
void menu() {
    while (true) {
        cout << "\n- Note Manager -\n\n";
        cout << "1. Create Note\n";
        cout << "2. View Notes\n";
        cout << "3. Read Note\n";
        cout << "4. Edit Note\n";
        cout << "5. Delete Note\n";
        cout << "6. Search Notes\n";
        cout << "0. Exit\n";
        cout << "Option: ";

        int choice;
        cin >> choice;

        if (choice == 1) createNote();
        else if (choice == 2) showNotes();
        else if (choice == 3) readNote();
        else if (choice == 4) editNote();
        else if (choice == 5) deleteNote();
        else if (choice == 6) searchNotes();
        else if (choice == 0) {
            cout << "Goodbye!\n";
            return;
        } else cout << "Why are you like this?\n";
    }
}

// entry point
// main is at the bottom of this instead of the top.
// i'm used to putting main at the top and using function prototypes but like...
// main can literally just be used to get the program to check for our foldery boi & then run the menu
// everything else is handled by functions. so why prototype at all.
// idk i get putting main at the bottom now tho lol, it's worth less when you don't cram it full of things.

int main() {
    makeNotesDirectory(); // does is are notes folder??
    menu();               // okay notes folder is there, fuck off to menu
    return 0;
} // rough line count is like 220 ish lines. under target but w/e
