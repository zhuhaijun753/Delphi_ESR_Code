#include "fileio.h"

fileIO::fileIO()
{
    frame_count = 0;
    file_num = 0;

}

void fileIO::set_filename(QString str){
    this->filename = str;
    file.setFileName(filename);
    file.open(QFile::WriteOnly | QFile::Truncate);
}

void fileIO::set_filename(){
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    filename = QString::number(date.year())+QString::number(date.month())+QString::number(date.day())+"_"+QString::number(time.hour())+QString::number(time.minute())+QString::number(time.second())+ "_"+QString::number(file_num)+".txt";
    file.setFileName(filename);
    file.open(QFile::WriteOnly| QFile::Append);
}

void fileIO::write(TRACK *track){
    QTextStream out(&file);

    if( frame_count == 30000 ){
        close();
        frame_count = 0;
        file_num++;
        set_filename();
    }

    out<<"@"<<QString::number(frame_count++)<<"\n";
    for(int i = 0; i < 64 ; i++){
        if(track[i].STATUS != 0){
            out<<"#"<<QString::number(track[i].id)<<":";
            for(int j = 0; j < 8 ; j++){
                out<<QString::number(track[i].hex[j])<<",";
            }
            out<<"\n";
        }
    }
}

void fileIO::close(){
    file.close();
}

void fileIO::read(QString filename){
    file.close();
    this->filename = filename;
    file.setFileName(filename);
    file.open(QFile::ReadOnly | QFile::Truncate);
    QTextStream in(&file);

    QString str,cstr;
    QStringList radar_list;

    int track_num;
    unsigned char hex[8];
    unsigned char bit[64];
    unsigned char out_bit[64];
    TRACK sig_track;
    while(!in.atEnd()){
        str=in.readLine();
        if(str.at(0) == '@'){
            cstr = "";
            for(int i = 1; i < str.size(); i++){
                cstr += str.at(i);
            }
            count = cstr.toInt();
        }else if(str.at(0) == '#'){
            cstr = "";
            for(int i = 1; i < str.size(); i++){
                cstr += str.at(i);
            }
            radar_list = cstr.split(":");
            track_num = radar_list.at(0).toInt();
            read_track[count][track_num].id = track_num;
            radar_list = radar_list.at(1).split(",");
            for(int i = 0; i < 8 ; i++){
                hex[i] = radar_list.at(i).toInt();
                read_track[count][track_num].hex[i] = hex[i];
            }

            convert_hexcode_to_bit(hex,bit);
            read_track[count][track_num] = analysis(bit,out_bit,sig_track);
        }
    }
}

int fileIO::get_frame_count(){
    return count;
}

TRACK* fileIO::get_read_track(int count){
    return read_track[count];
}

