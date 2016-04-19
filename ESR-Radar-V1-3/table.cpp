#include "table.h"
#include "ui_table.h"

Table::Table(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Table)
{
    //아이콘 리소스가 기입이 안됨 크기 할당 오류남
    //다른 FORM에서는 사용가능  , 따라서 이유를 모르겠음
    //
    ui->setupUi(this);
    //트랙
    track= new TRACK[MAX_TRACK_SIZE];
    //트랙 초기화
    for(int i = 0 ; i < MAX_TRACK_SIZE ; i++){
        track[i].AMP = 0;
        track[i].ANGLE = 0;
        track[i].BRIDGE = 0;
        track[i].GROUPING = 0;
        track[i].id = 0;
        track[i].LAT_RATE = 0;
        track[i].MED_RANGE_MODE = 0;
        track[i].ONCOMMING = 0;
        track[i].RANGE = 0;
        track[i].RANGE_ACCEL = 0;
        track[i].RANGE_RATE = 0;
        track[i].ROLLING = 0;
        track[i].STATUS = 0;
        track[i].WIDTH = 0;
        track[i].X = 0;
        track[i].Y = 0;
    }

    //트랙 정보
    table_value_name[0] = "Status";
    table_value_name[1] = "Range";
    table_value_name[2] = "HBr";
    table_value_name[3] = "Rate";
    table_value_name[4] = "Accel";
    table_value_name[5] = "Mode";

    //rule
    rule = new Rule();

    //
    ui->setupUi(this);
    background_table_line_color = Scalar(50,50,50);
    background_table_text_color = Scalar(150,150,150);

    //paint table
    //paint_background_table();
}

Table::~Table()
{
    delete ui;
}

void Table::paint_table(){
    //적용 룰
    rule->set_data_measurement(data_mesurement);
    //테이블 맵 초기화
    mat_table = Mat::zeros(LB_TABLE_HEIGHT,LB_TABLE_WIDTH,CV_8UC3);
    //패인트
    paint_value_table();
    paint_background_table();
    //출력
    ui->LB_Table->setPixmap(get_table());

}

void Table::paint_background_table(){

    rectangle(mat_table, Rect(0,0,LB_TABLE_WIDTH,LB_TABLE_HEIGHT),background_table_line_color);

    //putText(mat_table,"QString::number(i)",Point2f(300,300),1,0.6,background_table_text_color);
    //putText(paint 영역, 입력 문자 , 좌표 , ?? ,글씨 크기 , 색상)

    for(int i = 1; i < TABLE_HEIGHT_LINE_NUMABER ; i++){
        line(mat_table,Point(0,TABLE_HEIGHT_SIZE*i),Point(LB_TABLE_WIDTH,TABLE_HEIGHT_SIZE*i),background_table_line_color);
        putText(mat_table,QString::number(i-1).toStdString(),Point2f(20,(i+1)*TABLE_HEIGHT_SIZE),1,0.6,background_table_text_color);
    }
    for(int i = 0 ; i < TABLE_WIDTH_LINE_NUMBER ; i++){
        line(mat_table,Point(TABLE_WIDTH_SIZE*(i+1),0),Point(TABLE_WIDTH_SIZE*(i+1),LB_TABLE_HEIGHT),background_table_line_color);
        putText(mat_table,table_value_name[i].toStdString(),Point2f((i+1)*TABLE_WIDTH_SIZE,TABLE_HEIGHT_SIZE),1,0.6,background_table_text_color);
    }
}

void Table::paint_value_table(){

    //값입력
    QString str_value = "";
    for(int i = 0;  i < MAX_TRACK_SIZE ; i++){
        if(mouse_click_point[i].y() != 0){
            rectangle(mat_table, Rect(0,mouse_click_point[i].y()+1,TABLE_WIDTH_SIZE,TABLE_HEIGHT_SIZE-1),Scalar(0,40,0),-1);
            rectangle(mat_table, Rect(0,mouse_click_point[i].y()+1,LB_TABLE_WIDTH,TABLE_HEIGHT_SIZE-1),Scalar(0,140,0));
        }

        rule->set_track(track[i]);
        if(rule->analysis()){
            //상태 표시
            str_value.setNum(track[i].STATUS);
            putText(mat_table,str_value.toStdString(),Point2f((1)*TABLE_WIDTH_SIZE,TABLE_HEIGHT_SIZE*(i+2)),1,0.6,background_table_text_color);
            //거리
            str_value.setNum(track[i].RANGE);
            putText(mat_table,str_value.toStdString(),Point2f((2)*TABLE_WIDTH_SIZE,TABLE_HEIGHT_SIZE*(i+2)),1,0.6,background_table_text_color);
            //각도
            str_value.setNum(track[i].ANGLE);
            putText(mat_table,str_value.toStdString(),Point2f((3)*TABLE_WIDTH_SIZE,TABLE_HEIGHT_SIZE*(i+2)),1,0.6,background_table_text_color);
            //속도
            str_value.setNum(track[i].RANGE_RATE);
            putText(mat_table,str_value.toStdString(),Point2f((4)*TABLE_WIDTH_SIZE,TABLE_HEIGHT_SIZE*(i+2)),1,0.6,background_table_text_color);
            //가속도
            str_value.setNum(track[i].RANGE_ACCEL);
            putText(mat_table,str_value.toStdString(),Point2f((5)*TABLE_WIDTH_SIZE,TABLE_HEIGHT_SIZE*(i+2)),1,0.6,background_table_text_color);
            //추출한 센서(0 : 둘다 추출 x , 1 : MR 만 추출 , 2 : LR 만 추출 ,  3 : 둘다 추출)
            str_value.setNum(track[i].MED_RANGE_MODE);
            putText(mat_table,str_value.toStdString(),Point2f((6)*TABLE_WIDTH_SIZE,TABLE_HEIGHT_SIZE*(i+2)),1,0.6,background_table_text_color);
        }
    }
}

QPixmap Table::get_table(){
    QImage img_map = QImage((unsigned char*)mat_table.data, mat_table.cols, mat_table.rows, mat_table.step, QImage::Format_RGB888);
    return QPixmap::fromImage(img_map);
}

void Table::set_track_data(TRACK *track){
    this->track = track;
}

void Table::set_data_mesurement(Limit data_mesurement){
    this->data_mesurement = data_mesurement;
}


void Table::closeEvent(QCloseEvent *event){
    //종료 버튼설정(없어도 되는 부분)
    this->setVisible(false);
    event->accept();
}
void Table::mousePressEvent(QMouseEvent *event){

    QPoint p = event->pos();
    int track_num = p.y()/TABLE_HEIGHT_SIZE;
    int y = (p.y()/TABLE_HEIGHT_SIZE)*TABLE_HEIGHT_SIZE;

    if(event->button() == Qt::LeftButton){
        mouse_click_point[track_num].setY(y);
        //rectangle(mat_table, Rect(0,y+1,LB_TABLE_WIDTH,TABLE_HEIGHT_SIZE-1),Scalar(150,20,20),-1);
    }
    if(event->button() == Qt::RightButton){
        mouse_click_point[track_num].setY(0);
        //rectangle(mat_table, Rect(0,y+1,LB_TABLE_WIDTH,TABLE_HEIGHT_SIZE-1),Scalar(20,150,20),-1);
    }

    event->accept();
}
