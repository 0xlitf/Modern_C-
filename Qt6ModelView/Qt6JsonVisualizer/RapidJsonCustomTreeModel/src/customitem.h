#pragma once
#include <QVariant>
#include <QJsonValue>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

class CustomItem {
public:
    enum NumberType {
        kIntFlag = 0x0020,
        kUintFlag = 0x0040,
        kInt64Flag = 0x0080,
        kUint64Flag = 0x0100,
        kDoubleFlag = 0x0200
    };

    CustomItem(CustomItem* parent = nullptr)
        : m_parentItem(parent) {}

    CustomItem* child(int i) {
        CustomItem* m_childItem = m_childrenItems.value(i);
        if (m_childItem) {
            return m_childItem;
        }
        return nullptr;
    }
    ~CustomItem() {
        QHash<int, CustomItem*>::iterator it;
        for (it = m_childrenItems.begin(); it != m_childrenItems.end(); ++it) {
            delete it.value();
        }
        m_childrenItems.clear();
    }

    int childrenCount() { return m_childrenItems.count(); }
    bool hasChildren() { return m_childrenItems.count() > 0; }
    void addChild(CustomItem* child) {
        child->setParent(this);
        int i = m_childrenItems.count();
        m_childrenItems[i] = child;
    }

    void addAttribute(QList<QVariant> l) {
        m_attribute = l;
    }
    QList<QVariant> attribute() const { return m_attribute; }

    QVariant value(int column) {
        return m_attribute[column];
    }

    void setValue(int column, QVariant value) {
        m_attribute[column] = value;
    }

    QString elementName() const { return m_elementName; }
    void setElementName(const QString& newElementName) { m_elementName = newElementName; }

    void setParent(CustomItem* parent) { m_parentItem = parent; }
    CustomItem* parent() { return m_parentItem; }

    bool checked() const { return m_checked; }
    void setChecked(bool newChecked) { m_checked = newChecked; }

    rapidjson::Type itemType() const;
    void setType(const rapidjson::Type& type);

    QHash<int, CustomItem*> childrenItems() const;
    void setChildrenItems(const QHash<int, CustomItem*>& newChildrenItems);

    NumberType numberType() const;
    void setNumberType(NumberType newNumberType);

private:
    QList<QVariant> m_attribute{QVariant(), QVariant(), QVariant()};

    QHash<int, CustomItem*> m_childrenItems{};
    CustomItem* m_parentItem = nullptr;

    NumberType m_numberType;

    bool m_checked = false;
    QString m_elementName{};

    rapidjson::Type m_itemType;
};
