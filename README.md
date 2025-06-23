# qCmp
A program to visually compare between two sets of images.

![](example.gif)

# Compiling from Source
Requires `Qt 6.8` or higher, optionally with `Image Formats` module for wider format support.

The project can be built and installed using `cmake` as follows:

    mkdir build && cd build
    cmake -DCMAKE_BUILD_TYPE Release ..
    cmake --build . --config Release
    cmake --install .

It is recommended to use the `Ninja` generator while configuring as such:

    cmake -DCMAKE_BUILD_TYPE Release -G Ninja ..

# Usage
    qcmp.exe [options] dirs...

Options:

    -?, -h, --help           Displays help on commandline options.
    --help-all               Displays help, including generic Qt options.
    -v, --version            Displays version information.
    -1, --pattern1 <regex1>  Search pattern for first set.
    -2, --pattern2 <regex2>  Search pattern for second set.
    -r, --rows <n>           Number of rows.
    -c, --cols <m>           Number of columns.
    -t, --timer <s>          Timer interval in seconds.

Arguments:

    dirs                     Directories to search.

The patterns specified are matched against all files found in the directories (the patterns are matched without the file extension), and then paired up if they share the same basename, where the basename if defined as a concatenation of all captured regex groups.

After this a GUI interface is started which alternates between the image sets to provide easy visual comparison.
