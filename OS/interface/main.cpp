#include <QApplication>
#include <QLabel>
int main ( int lArgc, char * lArgv [ ] )
{
    QApplication lApplication ( lArgc, lArgv );
    QLabel lLabel;
    lLabel.setText ( "Текст на русском" );
    lLabel.setGeometry ( Qt::AlignHCenter, Qt::AlignVCenter, 500, 700 );
    lLabel.setAlignment (Qt::AlignHCenter | Qt::AlignVCenter );
    QFont lBlackFont ( " Times New Roman ", 12 );
    lLabel.setFont ( lBlackFont );
    lLabel.show ( );
    return lApplication.exec ( );
}
