#ifndef CPROFILE_LOAD_THREAD_H
#define CPROFILE_LOAD_THREAD_H

#include <QThread>
#include <QProcess>

#include "Model/qTagger/qTagger.h"

#include "Model/CProfileItem.h"
#include "Model/CRunCommand.h"
#include "Model/CConfigManager.h"  

class CProfileLoadThread: public QThread
{
	Q_OBJECT

public:
    CProfileLoadThread(QObject *parent = 0);
    
    void setCurrentProfileItem(const CProfileItem& profileItem);

	void setOutputItemListPtr(T_OutputItemList* outputItemListPtr);
	void setTaggerPtr(QTagger* taggerPtrPtr);

	CProfileItem getCurrentProfileItem(); 
    
    void run();

signals:
	void profileLoadPercentageCompleted(int percentage); 

private:
    bool runCommand(const QString& program, const QString& workDir, const QString& redirectFile = "");
    CProfileItem m_profileItem;

	CRunCommand m_cmd;
	QTagger* m_taggerPtr;

	T_OutputItemList* m_outputItemListPtr;
    
};

#endif // CPROFILE_LOAD_THREAD_H
