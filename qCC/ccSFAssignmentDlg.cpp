// ##########################################################################
// #                                                                        #
// #                              CLOUDCOMPARE                              #
// #                                                                        #
// #  This program is free software; you can redistribute it and/or modify  #
// #  it under the terms of the GNU General Public License as published by  #
// #  the Free Software Foundation; version 2 or later of the License.      #
// #                                                                        #
// #  This program is distributed in the hope that it will be useful,       #
// #  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
// #  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          #
// #  GNU General Public License for more details.                          #
// #                                                                        #
// #          COPYRIGHT: Antigravity AI                                     #
// #                                                                        #
// ##########################################################################

#include "ccSFAssignmentDlg.h"

// qCC_db
#include <ccPointCloud.h>
#include <ccScalarField.h>
#include <ccHObjectCaster.h>
#include <ccLog.h>

// Qt
#include <QSet>

ccSFAssignmentDlg::ccSFAssignmentDlg(const ccHObject::Container& entities, QWidget* parent)
	: QDialog(parent)
	, Ui::SFAssignmentDlg()
	, m_entities(entities)
{
	setupUi(this);

	setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);

	connect(sfComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &ccSFAssignmentDlg::onSFChanged);
	connect(applyButton, &QPushButton::clicked, this, &ccSFAssignmentDlg::onApply);
	connect(valuesListWidget, &QListWidget::itemDoubleClicked, this, &ccSFAssignmentDlg::onValueDoubleClicked);

	// Populate SF combo box
	QSet<QString> sfNames;
	for (ccHObject* entity : m_entities)
	{
		ccPointCloud* pc = ccHObjectCaster::ToPointCloud(entity);
		if (pc)
		{
			for (unsigned i = 0; i < pc->getNumberOfScalarFields(); ++i)
			{
				sfNames.insert(QString(pc->getScalarFieldName(i).c_str()));
			}
		}
	}

	QStringList sortedNames = sfNames.values();
	sortedNames.sort();
	sfComboBox->addItems(sortedNames);

    // Initial refresh
    refreshValues();
}

void ccSFAssignmentDlg::onSFChanged(int index)
{
    refreshValues();
}

void ccSFAssignmentDlg::refreshValues()
{
    valuesListWidget->clear();

    QString currentSFName = sfComboBox->currentText();
    if (currentSFName.isEmpty())
        return;

    QSet<ScalarType> uniqueValues;
    for (ccHObject* entity : m_entities)
    {
        ccPointCloud* pc = ccHObjectCaster::ToPointCloud(entity);
        if (pc)
        {
            int sfIdx = pc->getScalarFieldIndexByName(currentSFName.toStdString().c_str());
            if (sfIdx >= 0 && sfIdx < static_cast<int>(pc->getNumberOfScalarFields()))
            {
                ccScalarField* sf = static_cast<ccScalarField*>(pc->getScalarField(sfIdx));
                const ccGenericPointCloud::VisibilityTableType& visibilityArray = pc->getTheVisibilityArray();

                for (unsigned i = 0; i < pc->size(); ++i)
                {
                    // Here we assume the visibility array has been updated by the tool
                    // to reflect the current selection.
                    if (visibilityArray.empty() || visibilityArray[i] == CCCoreLib::POINT_VISIBLE)
                    {
                        uniqueValues.insert(sf->getValue(i));
                    }
                }
            }
        }
    }

    QList<ScalarType> sortedValues = uniqueValues.values();
    std::sort(sortedValues.begin(), sortedValues.end());

    for (ScalarType val : sortedValues)
    {
        valuesListWidget->addItem(QString::number(val));
    }
}

void ccSFAssignmentDlg::onApply()
{
    QString sfName = sfComboBox->currentText();
    if (sfName.isEmpty())
        return;

    ScalarType value = static_cast<ScalarType>(valueSpinBox->value());
    emit applyValue(sfName, value);
}

void ccSFAssignmentDlg::onValueDoubleClicked(QListWidgetItem* item)
{
    if (item)
    {
        valueSpinBox->setValue(item->text().toDouble());
    }
}

ScalarType ccSFAssignmentDlg::getAssignedValue() const
{
    return static_cast<ScalarType>(valueSpinBox->value());
}

QString ccSFAssignmentDlg::getSFName() const
{
    return sfComboBox->currentText();
}
