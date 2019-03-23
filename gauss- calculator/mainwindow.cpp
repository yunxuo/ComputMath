#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    getRadio.addButton(ui->radioButton, 1);
    getRadio.addButton(ui->radioButton_2, 2);


    Label_x[0] = ui->label;
    Label_x[1] = ui->label_2;
    Label_x[2] = ui->label_3;
    Label_x[3] = ui->label_4;
    Label_x[4] = ui->label_5;
    Label_x[5] = ui->label_6;


    LineEdit_2[0] = ui->lineEdit;
    LineEdit_2[1] = ui->lineEdit_2;
    LineEdit_2[2] = ui->lineEdit_10;
    LineEdit_2[3] = ui->lineEdit_12;

    for(int i=0;i<4;i++)
        LineEdit_3[i] = LineEdit_2[i];

    LineEdit_3[4] = ui->lineEdit_3;
    LineEdit_3[5] = ui->lineEdit_8;
    LineEdit_3[6] = ui->lineEdit_16;
    LineEdit_3[7] = ui->lineEdit_15;
    LineEdit_3[8] = ui->lineEdit_13;

    for(int i=0;i<9;i++)
        LineEdit_4[i] = LineEdit_3[i];

    LineEdit_4[9] = ui->lineEdit_4;
    LineEdit_4[10] = ui->lineEdit_11;
    LineEdit_4[11] = ui->lineEdit_14;
    LineEdit_4[12] = ui->lineEdit_24;
    LineEdit_4[13] = ui->lineEdit_22;
    LineEdit_4[14] = ui->lineEdit_21;
    LineEdit_4[15] = ui->lineEdit_20;

    for(int i=0;i<16;i++)
        LineEdit_5[i] = LineEdit_4[i];

    LineEdit_5[16] = ui->lineEdit_5;
    LineEdit_5[17] = ui->lineEdit_9;
    LineEdit_5[18] = ui->lineEdit_18;
    LineEdit_5[19] = ui->lineEdit_19;
    LineEdit_5[20] = ui->lineEdit_30;
    LineEdit_5[21] = ui->lineEdit_25;
    LineEdit_5[22] = ui->lineEdit_29;
    LineEdit_5[23] = ui->lineEdit_26;
    LineEdit_5[24] = ui->lineEdit_27;


    LineEdit_y[0] = ui->lineEdit_6;
    LineEdit_y[1] = ui->lineEdit_7;
    LineEdit_y[2] = ui->lineEdit_17;
    LineEdit_y[3] = ui->lineEdit_23;
    LineEdit_y[4] = ui->lineEdit_28;


    for(int i =0;i<6;i++)
        Label_x[i]->setVisible(false);
    for(int i =0;i<25;i++)
        LineEdit_5[i]->setVisible(false);
    for(int i =0;i<5;i++)
        LineEdit_y[i]->setVisible(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}

vector<double> MainWindow::cal_gauss_cols(vector<vector<double> > a)
{
    double ratio, sum;
    result.resize(num);
    int max_index;
    double max_elem = 0.00000001;

    for(int k = 0; k<(num - 1); k++)
    {
        //找主元
        for(int find_index = 0; find_index<num; find_index++)
        {
            if(a[find_index][k] > max_elem)
            {
                max_elem = a[find_index][k];
                max_index = find_index;
            }

        }

        //交换行
        if (max_elem<EPS)   //fabs(x)函数是求浮点型数x的绝对值
        {
            cout << endl << "[error] The element is too small..." << endl;
            exit(0);
        }
        else if(max_index != k)
        {
            for(int swap_rows = k; swap_rows<=num;swap_rows++)
            {
                double _temp = a[k][swap_rows];
                a[k][swap_rows] = a[max_index][swap_rows];
                a[max_index][swap_rows] = _temp;
            }
        }
        //计算
        for(int _rows = k+1;_rows<num;_rows++)
        {
            ratio = a[_rows][k]/a[k][k];
            for(int _cols = k+1; _cols<=num;_cols++)
            {
                a[_rows][_cols] -= a[k][_cols]*ratio;
            }
        }
    }
    //回代
    result[num - 1] = a[num - 1][num] / a[num - 1][num - 1]; //回代
    for (int i = (num - 2); i >= 0; --i)
    {
        sum = 0.0;
        for (int j = (i + 1); j<num; j++)
        {
            sum += a[i][j] * result[j];
        }
        result[i] = (a[i][num] - sum) / a[i][i];
    }

    return result;
}

vector<double> MainWindow::cal_gauss_order(vector<vector<double> > a)
{
    double ratio, sum;
    result.resize(num);

    for (int k = 0; k<(num - 1); k++)      //消元
    {
        for (int i = (k + 1); i<num; i++)
        {
            if (fabs(a[k][k])<EPS)   //fabs(x)函数是求浮点型数x的绝对值
            {
                cout << endl << "[error] The element is too small..." << endl;
                exit(0);
            }
            ratio = a[i][k] / a[k][k];
            for (int j = (k + 1); j <= num; j++)
            {
                a[i][j] -= ratio*a[k][j];
            }
            a[i][k] = 0;
        }
    }
    result[num - 1] = a[num - 1][num] / a[num - 1][num - 1]; //回代
    for (int i = (num - 2); i >= 0; --i)
    {
        sum = 0.0;
        for (int j = (i + 1); j<num; j++)
        {
            sum += a[i][j] * result[j];
        }
        result[i] = (a[i][num] - sum) / a[i][i];
    }
    return result;
}

QString MainWindow::display_label(vector<double> result)
{
    QString display;

    string _temp = "Result: \n";
    for(int i =0;i<result.size();i++)
    {
        _temp += "x" + std::to_string(i+1) + " = " + std::to_string(result[i]) + "\n";
    }

    display = QString::fromStdString(_temp);

    return display;

}

void MainWindow::on_pushButton_clicked()
{
    num =1;

    Label_x[0]->setVisible(true);
    Label_x[5]->setVisible(true);
    ui->lineEdit->setVisible(true);
    LineEdit_y[0]->setVisible(true);

}

void MainWindow::on_pushButton_2_clicked()
{
    num = 2;
    Label_x[5]->setVisible(true);

    for(int i =0;i<num;i++)
    {
        LineEdit_3[i]->setVisible(true);
        LineEdit_3[i+num*1]->setVisible(true);
        Label_x[i]->setVisible(true);
        LineEdit_y[i]->setVisible(true);
    }

}

void MainWindow::on_pushButton_3_clicked()
{
    num = 3;
    Label_x[5]->setVisible(true);



    for(int i =0;i<num;i++)
    {
        LineEdit_3[i]->setVisible(true);
        LineEdit_3[i+num*1]->setVisible(true);
        LineEdit_3[i+num*2]->setVisible(true);
        Label_x[i]->setVisible(true);
        LineEdit_y[i]->setVisible(true);
    }

}

void MainWindow::on_pushButton_4_clicked()
{
    num = 4;
    Label_x[5]->setVisible(true);


    for(int i =0;i<num;i++)
    {
        LineEdit_4[i]->setVisible(true);
        LineEdit_4[i+num*1]->setVisible(true);
        LineEdit_4[i+num*2]->setVisible(true);
        LineEdit_4[i+num*3]->setVisible(true);
        Label_x[i]->setVisible(true);
        LineEdit_y[i]->setVisible(true);
    }

}

void MainWindow::on_pushButton_5_clicked()
{
    num = 5;
    Label_x[5]->setVisible(true);


    for(int i =0;i<num;i++)
    {
        LineEdit_5[i]->setVisible(true);
        LineEdit_5[i+num*1]->setVisible(true);
        LineEdit_5[i+num*2]->setVisible(true);
        LineEdit_5[i+num*3]->setVisible(true);
        LineEdit_5[i+num*4]->setVisible(true);
        Label_x[i]->setVisible(true);
        LineEdit_y[i]->setVisible(true);
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    for(int i =0;i<6;i++)
        Label_x[i]->setVisible(false);
    for(int i =0;i<25;i++)
    {
        LineEdit_5[i]->clear();
        LineEdit_5[i]->setVisible(false);
    }

    for(int i =0;i<5;i++)
    {
        LineEdit_y[i]->clear();
        LineEdit_y[i]->setVisible(false);
    }

    ui->label_result->clear();
    result.clear();
    output.clear();
    num = 0;
}


void MainWindow::on_pushButton_6_clicked()
{
    input.clear();
    switch (num)
    {
        case 1:
        {
            double x_1_1 = ui->lineEdit->text().toDouble();
            double y_1 = LineEdit_y[0]->text().toDouble();
            double _result = y_1 / x_1_1;
            output.sprintf("%s %f", "x1 = ", _result);
            ui->label_result->setText(output);
            break;
        }
        case 2:
        {
            input.resize(num);
            for(int i = 0; i < num; i++)
            {
                input[0].push_back(LineEdit_2[i]->text().toDouble());
                input[1].push_back(LineEdit_2[num*2 - i - 1]->text().toDouble());
            }
            for(int i = 0; i < num; i++)
            {
                input[i].push_back(LineEdit_y[i]->text().toDouble());
            }
            break;
        }
        case 3:
        {
            input.resize(num);

            input[0].push_back(LineEdit_3[0]->text().toDouble());
            input[0].push_back(LineEdit_3[1]->text().toDouble());
            input[0].push_back(LineEdit_3[4]->text().toDouble());
            input[1].push_back(LineEdit_3[3]->text().toDouble());
            input[1].push_back(LineEdit_3[2]->text().toDouble());
            input[1].push_back(LineEdit_3[5]->text().toDouble());

            for(int i = 0; i < num; i++)
            {
                input[num-1].push_back(LineEdit_3[num*num - 1 - i]->text().toDouble());
            }

            for(int i = 0; i < num; i++)
            {
                input[i].push_back(LineEdit_y[i]->text().toDouble());
            }
            break;
        }
        case 4:
        {
            input.resize(num);

            input[0].push_back(LineEdit_3[0]->text().toDouble());
            input[0].push_back(LineEdit_3[1]->text().toDouble());
            input[0].push_back(LineEdit_3[4]->text().toDouble());
            input[0].push_back(LineEdit_4[9]->text().toDouble());

            input[1].push_back(LineEdit_3[3]->text().toDouble());
            input[1].push_back(LineEdit_3[2]->text().toDouble());
            input[1].push_back(LineEdit_3[5]->text().toDouble());
            input[1].push_back(LineEdit_4[10]->text().toDouble());

            for(int i = 0; i < num -1; i++)
            {
                input[num-2].push_back(LineEdit_3[((num-1)*(num-1)) - 1 - i]->text().toDouble());
            }

            input[2].push_back(LineEdit_4[11]->text().toDouble());

            for(int i = 0; i < num; i++)
            {
                input[num-1].push_back(LineEdit_4[num*num - 1 - i]->text().toDouble());
            }

            for(int i = 0; i < num; i++)
            {
                input[i].push_back(LineEdit_y[i]->text().toDouble());
            }
            break;
        }
        case 5:
        {

            input.resize(num);

            input[0].push_back(LineEdit_3[0]->text().toDouble());
            input[0].push_back(LineEdit_3[1]->text().toDouble());
            input[0].push_back(LineEdit_3[4]->text().toDouble());
            input[0].push_back(LineEdit_4[9]->text().toDouble());
            input[0].push_back(LineEdit_5[16]->text().toDouble());

            input[1].push_back(LineEdit_3[3]->text().toDouble());
            input[1].push_back(LineEdit_3[2]->text().toDouble());
            input[1].push_back(LineEdit_3[5]->text().toDouble());
            input[1].push_back(LineEdit_4[10]->text().toDouble());
            input[1].push_back(LineEdit_5[17]->text().toDouble());

            for(int i = 0; i < num -2; i++)
            {
                input[num-3].push_back(LineEdit_3[((num-2)*(num-2)) - 1 - i]->text().toDouble());
            }
            input[2].push_back(LineEdit_5[11]->text().toDouble());
            input[2].push_back(LineEdit_5[18]->text().toDouble());

            for(int i = 0; i < num -1; i++)
            {
                input[num-2].push_back(LineEdit_4[((num-1)*(num-1)) - 1 - i]->text().toDouble());
            }
            input[3].push_back(LineEdit_5[19]->text().toDouble());

            for(int i = 0; i < num; i++)
            {
                input[num-1].push_back(LineEdit_5[num*num - 1 - i]->text().toDouble());
            }

            for(int i = 0; i < num; i++)
            {
                input[i].push_back(LineEdit_y[i]->text().toDouble());
            }      
//            qDebug()<<input[0][0]<<input[0][1]<<input[0][2]<<input[0][3]<<input[0][4]<<input[0][5]<<"\n"
//                    <<input[1][0]<<input[1][1]<<input[1][2]<<input[1][3]<<input[1][4]<<input[1][5]<<"\n"
//                    <<input[2][0]<<input[2][1]<<input[2][2]<<input[2][3]<<input[2][4]<<input[2][5]<<"\n"
//                    <<input[3][0]<<input[3][1]<<input[3][2]<<input[3][3]<<input[3][4]<<input[3][5]<<"\n"
//                    <<input[4][0]<<input[4][1]<<input[4][2]<<input[4][3]<<input[4][4]<<input[4][5]<<"\n";
            break;
        }
        default:
            break;
    }
    if(num>1)
    {
        if(getRadio.checkedId() == 1)
            result = cal_gauss_order(input);
        else
            result = cal_gauss_cols(input);
        output = display_label(result);
        ui->label_result->setText(output);
    }
}


