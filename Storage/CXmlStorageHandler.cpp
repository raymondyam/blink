#include <QFile>
#include <QMessageBox>
#include <QtXml>
#include <QMap>

#include <iostream>
#include "CXmlStorageHandler.h"

BYTE CXmlStorageHandler::loadFromFile(const QString& filename, QMap<QString, CProfileItem>& profileMap, QMap<QString, CGroupItem>& groupMap)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        return LoadFileError;
    }

    QDomDocument doc("ProfileML");

	QString errMsg;
	int errLine, errCol;

    if (!doc.setContent(&file, false, &errMsg, &errLine, &errCol)) {
        qDebug() << "QDomDocument setContent() failed in CXmlStorageHandler::loadFromFile()!" << endl;  
		qDebug() << "err:" << errMsg << ", line:" << errLine << " column:" << errCol << endl;
		file.close();
        return LoadFileError;
    }

    file.close();

	QDomElement docElement = doc.documentElement(); 
	
	// start from doc first child
	QDomNode docNode = docElement.firstChild();  

	while (!docNode.isNull()) { 
		QDomElement rootItem = docNode.toElement();

		if (rootItem.tagName() == "profile") {
			profileMap.clear();
			QDomNode node = rootItem.firstChild();

			while (!node.isNull()) {
			   QDomElement element = node.toElement();
			   if (!element.isNull()) {
				  if (element.tagName() == "profileItem") {
					  CProfileItem item;

					  fillProfileItem(item, element);
					  profileMap[element.attribute("name", "")] = item;
				  }
				  node = node.nextSibling();
			   }
			}
		} else if (rootItem.tagName() == "group") {
			groupMap.clear();
			QDomNode node = rootItem.firstChild();

			while (!node.isNull()) {
			   QDomElement element = node.toElement();
			   if (!element.isNull()) {
				  if (element.tagName() == "groupItem") {
					  CGroupItem item;

					  fillGroupItem(item, element);
					  groupMap[element.attribute("name", "")] = item;
				  }
				  node = node.nextSibling();
			   }
			}
		}
		docNode = docNode.nextSibling(); 
	}

    return NoError;
}

QDomElement CXmlStorageHandler::createXMLNode(QDomDocument &document, const CProfileItem &profileItem)
{
    QDomElement element = document.createElement("profileItem");

    element.setAttribute("name", profileItem.m_name);
    element.setAttribute("srcDir", profileItem.m_srcDir);
    element.setAttribute("srcMask", profileItem.m_srcMask);
    element.setAttribute("headerMask", profileItem.m_headerMask);
	element.setAttribute("tagUpdateDateTime", profileItem.m_tagUpdateDateTime); 
	element.setAttribute("profileCreateDateTime", profileItem.m_profileCreateDateTime); 
    element.setAttribute("labels", profileItem.m_labels);  

    return element;
}

QDomElement CXmlStorageHandler::createXMLNode(QDomDocument &document, const CGroupItem &groupItem)
{
    QDomElement element = document.createElement("groupItem");

    element.setAttribute("name", groupItem.m_name);
    element.setAttribute("profileList", groupItem.m_profileList);
	element.setAttribute("tagUpdateDateTime", groupItem.m_tagUpdateDateTime); 
	element.setAttribute("groupCreateDateTime", groupItem.m_groupCreateDateTime); 
    element.setAttribute("labels", groupItem.m_labels);  

    return element;
} 

void CXmlStorageHandler::fillProfileItem(CProfileItem& profileItemToBeFill, const QDomElement& element)
{
	QString name, srcDir, srcMask, headerMask;
	QString tagUpdateDateTime, profileCreateDateTime;

    QString labels;
    
    name = element.attribute("name", "");
    srcDir = element.attribute("srcDir", ""); 
    srcMask = element.attribute("srcMask", ""); 
    headerMask = element.attribute("headerMask", "");
    labels = element.attribute("labels", "");

	tagUpdateDateTime = element.attribute("tagUpdateDateTime", ""); 
	profileCreateDateTime = element.attribute("profileCreateDateTime", ""); 
    
	CProfileItem profileItem(name, srcDir, srcMask, headerMask, 
		tagUpdateDateTime, profileCreateDateTime, labels);

	profileItemToBeFill = profileItem;
}

void CXmlStorageHandler::fillGroupItem(CGroupItem& groupItemToBeFill, const QDomElement& element)
{
	QString name;
	QString profileList;
	QString tagUpdateDateTime, groupCreateDateTime; 
    QString labels;
    
    name = element.attribute("name", "");
	profileList = element.attribute("profileList", "");

	tagUpdateDateTime = element.attribute("tagUpdateDateTime", ""); 
	groupCreateDateTime = element.attribute("groupCreateDateTime", ""); 
	
    labels = element.attribute("labels", "");

	CGroupItem groupItem(name, profileList, tagUpdateDateTime, groupCreateDateTime, labels);

	groupItemToBeFill = groupItem;
}


BYTE CXmlStorageHandler::saveToFile(const QString& filename, const QMap<QString, CProfileItem>& profileMap, const QMap<QString, CGroupItem>& groupMap)
{
    QDomDocument doc("ProfileML");

	// record
	QDomElement recordRoot = doc.createElement("record"); 
	doc.appendChild(recordRoot); 

	// profile
    QDomElement profileRoot = doc.createElement("profile");
    recordRoot.appendChild(profileRoot);

    CProfileItem profileItem;
    foreach (profileItem, profileMap) {
        QDomElement node = createXMLNode(doc, profileItem);
        profileRoot.appendChild(node);
    }

	// group
    QDomElement groupRoot = doc.createElement("group");
    recordRoot.appendChild(groupRoot);

    CGroupItem groupItem;
    foreach (groupItem, groupMap) {
        QDomElement node = createXMLNode(doc, groupItem);
        groupRoot.appendChild(node);
    }

#ifdef DEBUG_XML
    QDomElement element = doc.createElement("profileItem");
    element.setAttribute("name", "a1");
    element.setAttribute("srcDir", "a2"); 
    element.setAttribute("srcMask", "a3"); 
    element.setAttribute("headerMask", "a4");
    element.setAttribute("labels", "a5");
    root.appendChild(element); 
#endif

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        //QMessageBox::warning(this, "Saving", "Failed to save file.", QMessageBox::Ok, QMessageBox::NoButton);  /* <-- YCH modified 31/08/06, just for reference, to be removed */
        return SaveFileError;
    }

    QTextStream ts(&file);
    ts << doc.toString();
    file.close();

    return NoError;
}


