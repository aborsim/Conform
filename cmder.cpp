//Command Runner
//Runs command and returns output

#ifdef __linux__
    #define POPEN popen
    #define PCLOSE pclose
#else
    #define POPEN _popen
    #define PCLOSE _pclose
#endif


QString cmder(QString cmd) {
    QByteArray ba(cmd.toLocal8Bit());
    FILE* pipe = popen(ba.data(), "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    QString result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}
