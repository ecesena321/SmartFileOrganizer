#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <cctype>
#include <system_error>

using namespace std;
namespace fs = filesystem;


class FileOrganizer
{
private:
    string folderPath;

public:
    FileOrganizer(string path)
    {
        folderPath = path;
    }

    void createFolders()
    {
        fs::create_directory(folderPath + "\\Images");
        fs::create_directory(folderPath + "\\Videos");
        fs::create_directory(folderPath + "\\Audio");
        fs::create_directory(folderPath + "\\Documents");
        fs::create_directory(folderPath + "\\Code");
        fs::create_directory(folderPath + "\\Other");
    }

    void scanFiles()
    {
        for (const auto& file : fs::directory_iterator(folderPath))
        {
            if (!file.is_regular_file())
            {
                continue;
            }

            cout << file.path().filename().string() << endl;
        }
    }
    
};





    int main()
{
    string folderPath;
    int imageCount = 0;
    int videoCount = 0;
    int audioCount = 0;
    int documentCount = 0;
    int codeCount = 0;
    int otherCount = 0;
    int totalCount = 0;



    // Dosya uzantisina gore kategoriyi belirler.

vector<fs::path> sourcePaths;
vector<fs::path> destinationPaths;
vector<size_t> movedIndices;

cout << "Klasor yolunu gir: ";
getline(cin >> ws, folderPath);

if (!fs::exists(folderPath) || !fs::is_directory(folderPath))
{
    cout << "Gecersiz klasor yolu!" << endl;
    return 1;
}


FileOrganizer organizer(folderPath);






// KLASÖRLER BURADA OLUŞTURULACAK
fs::create_directory(folderPath + "\\Images");
fs::create_directory(folderPath + "\\Videos");
fs::create_directory(folderPath + "\\Audio");
fs::create_directory(folderPath + "\\Documents");
fs::create_directory(folderPath + "\\Code");
fs::create_directory(folderPath + "\\Other");

for (const auto& file : fs::directory_iterator(folderPath))
{
    if (!file.is_regular_file())
{
    continue;
}
    totalCount++;
    string extension = file.path().extension().string();
    for (char& c : extension)
{
    c = tolower(c);
}
    string category;

cout << extension;

if (extension == ".jpg" || extension == ".jpeg" ||
    extension == ".png" || extension == ".gif")
{
    category = "Images";
    imageCount++;
}
else if (extension == ".mp4" || extension == ".avi" ||
         extension == ".mov" || extension == ".mkv")
{
    category = "Videos";
    videoCount++;
}
else if (extension == ".mp3" || extension == ".wav" ||
         extension == ".flac" || extension == ".aac")
{
    category = "Audio";
    audioCount++;
}
else if (extension == ".txt" || extension == ".docx" ||
        extension == ".pptx" || extension == ".ppt"||
         extension == ".pdf" || extension == ".xlsx")
{
    category = "Documents";
    documentCount++;
}
else if (extension == ".cpp" || extension == ".h" ||
         extension == ".hpp")
{
    category = "Code";
    codeCount++;
}

else
{
    category = "Other";
    otherCount++;

    cout << "Other file: "
         << file.path().filename().string()
         << endl;
}

cout << " -> " << category << endl;
string destination = folderPath + "\\" + category + "\\" + file.path().filename().string();

cout << destination << endl;
sourcePaths.push_back(file.path());
destinationPaths.push_back(destination);
//fs::rename(file.path(), destination);
}
cout << "\n--- DOSYA ONIZLEMESI ---" << endl;

for (size_t i = 0; i < sourcePaths.size(); i++)
{
    cout << sourcePaths[i].filename().string()
         << " -> "
         << destinationPaths[i].parent_path().filename().string()
         << endl;
}

char answer;
int movedCount = 0;

cout << "\nDosyalar tasinsin mi? (e/h): ";
cin >> answer;

if (answer == 'e' || answer == 'E')
{
    
    for (size_t i = 0; i < sourcePaths.size(); i++)
    {
        if (fs::exists(destinationPaths[i]))
{
    cout << "Bu isimde bir dosya zaten var: "
         << destinationPaths[i].filename().string()
         << endl;
}
else
{
    error_code ec;
fs::rename(sourcePaths[i], destinationPaths[i], ec);

if (!ec)
{
    movedCount++;
    movedIndices.push_back(i);
}
else
{
    cout << "Dosya tasinamadi: "
         << sourcePaths[i].filename().string()
         << " | Hata: " << ec.message() << endl;
}
} 
    }

    cout << "Tasinan dosya sayisi: " << movedCount << endl;
}
else
{
    cout << "Dosya tasima islemi iptal edildi." << endl;
}

if (movedCount > 0)
{
    char undoChoice;

    cout << "Tasima islemini geri almak ister misin? (e/h): ";
    cin >> undoChoice;

    if (undoChoice == 'e' || undoChoice == 'E')
    {
        int restoredCount = 0;

        for (size_t index : movedIndices)
        {
            error_code ec;

            if (fs::exists(sourcePaths[index]))
            {
                cout << "Eski konumda ayni isimli dosya var: "
                     << sourcePaths[index].filename().string()
                     << endl;
                continue;
            }

            fs::rename(destinationPaths[index], sourcePaths[index], ec);

            if (!ec)
            {
                restoredCount++;
            }
            else
            {
                cout << "Dosya geri alinamadi: "
                     << destinationPaths[index].filename().string()
                     << " | Hata: " << ec.message() << endl;
            }
        }

        cout << "Geri alinan dosya sayisi: "
             << restoredCount << endl;
    }
}

int currentImages = 0;
int currentVideos = 0;
int currentAudio = 0;
int currentDocuments = 0;
int currentCode = 0;
int currentOther = 0;
int currentTotal = 0;

for (const auto& file : fs::directory_iterator(folderPath))
{
    if (!file.is_regular_file())
    {
        continue;
    }

    currentTotal++;

    string extension = file.path().extension().string();

    for (char& c : extension)
    {
        c = tolower(c);
    }

    if (extension == ".jpg" || extension == ".jpeg" ||
        extension == ".png" || extension == ".gif")
    {
        currentImages++;
    }
    else if (extension == ".mp4" || extension == ".avi" ||
             extension == ".mov" || extension == ".mkv")
    {
        currentVideos++;
    }
    else if (extension == ".mp3" || extension == ".wav" ||
             extension == ".flac" || extension == ".aac")
    {
        currentAudio++;
    }
    else if (extension == ".txt" || extension == ".docx" ||
             extension == ".pptx" || extension == ".ppt" ||
             extension == ".pdf" || extension == ".xlsx")
    {
        currentDocuments++;
    }
    else if (extension == ".cpp" || extension == ".h" ||
             extension == ".hpp")
    {
        currentCode++;
    }
    else
    {
        currentOther++;
    }
}



cout << "\n========== GUNCEL KLASOR RAPORU ==========" << endl;
cout << "Ana klasorde kalan resim dosyalari: " << currentImages << endl;
cout << "Ana klasorde kalan video dosyalari: " << currentVideos << endl;
cout << "Ana klasorde kalan ses dosyalari: " << currentAudio << endl;
cout << "Ana klasorde kalan belge dosyalari: " << currentDocuments << endl;
cout << "Ana klasorde kalan kod dosyalari: " << currentCode << endl;
cout << "Ana klasorde kalan diger dosyalar: " << currentOther << endl;
cout << "Ana klasorde kalan toplam dosya: " << currentTotal << endl;
cout << "==========================================" << endl;


for (const auto& file : fs::directory_iterator(folderPath))
{
    if (!file.is_regular_file())
    {
        continue;
    }

    currentTotal++;

    string extension = file.path().extension().string();

    for (char& c : extension)
    {
        c = tolower(c);
    }

    if (extension == ".jpg" || extension == ".jpeg" ||
        extension == ".png" || extension == ".gif")
    {
        currentImages++;
    }
    else if (extension == ".mp4" || extension == ".avi" ||
             extension == ".mov" || extension == ".mkv")
    {
        currentVideos++;
    }
    else if (extension == ".mp3" || extension == ".wav" ||
             extension == ".flac" || extension == ".aac")
    {
        currentAudio++;
    }
    else if (extension == ".txt" || extension == ".docx" ||
             extension == ".pptx" || extension == ".ppt" ||
             extension == ".pdf" || extension == ".xlsx")
    {
        currentDocuments++;
    }
    else if (extension == ".cpp" || extension == ".h" ||
             extension == ".hpp")
    {
        currentCode++;
    }
    else
    {
        currentOther++;
    }
}


    return 0;
}