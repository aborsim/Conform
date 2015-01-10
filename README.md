## DISCLAIMER: VERY BUGGY. EVEN THE INSTRUCTIONS MAY BE WRONG.

# Description
I was looking around for a good open source GPL batch converter. But every single one I found seemed to be slow and only able to process one file at a time. So I wrote an FFmpeg wrapper that can take on several files at once. Enjoy! And report any bugs you find so that I can fix them. :)

# Building Instructions
This project has only been tested to work on Linux (Linux Mint 17) and is unlikely to work on any other OS at the moment. It project requires Qt5, FFmpeg, and jsoncpp. The following commands should have you covered:
```
sudo add-apt-repository ppa:ppa:mc3man/trusty-media
sudo apt-get update
sudo apt-get qtdeclarative5-dev cmake ffmpeg
git clone https://github.com/open-source-parsers/jsoncpp.git
cd jsoncpp
cmake .
make && sudo make install
```
Now, onto building it:
```
git clone https://github.com/aborsim/Conform.git
cd Conform
qmake .
make
```

# Contributing
Get the latest version of Qt 5, which should also install Qt Creator:
```
wget http://download.qt-project.org/official_releases/online_installers/qt-opensource-linux-x64-online.run
chmod +x qt-opensource-linux-x64-online.run
sudo ./qt-opensource-linux-x64-online.run
```

I *highly* suggest you develop this project in Qt Creator as this project was created with Qt and I used it for development.




