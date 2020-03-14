/////////////////////////////////////////////////////////////////////////////
// Name:    democollection.cpp
// Purpose: Demo collection class implementation
// Author:    Moskvichev Andrey V.
// Created:    2008/11/12
// Copyright:    (c) 2008-2009 Moskvichev Andrey V.
// Licence:    wxWidgets licence
/////////////////////////////////////////////////////////////////////////////

#include "democollection.h"

// demos
extern ChartDemo *xyDemos[];
extern int xyDemosCount;

extern ChartDemo *pieplotDemos[];
extern int pieplotDemosCount;


static DemoCollection instance;

/**
 * Demo category.
 */
class Category
{
public:
    Category(wxString name, ChartDemo **charts, int chartCount)
    {
        m_name = name;
        m_chartDemos = charts;
        m_chartCount = chartCount;
    }

    const wxString &GetName()
    {
        return m_name;
    }

    const wxString &GetChartName(int chartIndex)
    {
        return m_chartDemos[chartIndex]->GetName();
    }

    ChartDemo *GetChartDemo(int chartIndex)
    {
        return m_chartDemos[chartIndex];
    }

    int GetChartCount()
    {
        return m_chartCount;
    }

private:
    wxString m_name;
    ChartDemo **m_chartDemos;
    int m_chartCount;
};

// demo categories
static Category *cats[] = {
    new Category(wxT("XY Charts"), xyDemos, xyDemosCount),
    new Category(wxT("Pie plots"), pieplotDemos, pieplotDemosCount),
};

//
// DemoCollection
//
DemoCollection::DemoCollection()
{
}

DemoCollection::~DemoCollection()
{
}

int DemoCollection::GetCategoryCount()
{
    return WXSIZEOF(cats);
}

const wxString &DemoCollection::GetCategory(int index)
{
    return cats[index]->GetName();
}

int DemoCollection::GetCategoryDemoCount(int index)
{
    return cats[index]->GetChartCount();
}

ChartDemo *DemoCollection::GetCategoryDemo(int catIndex, int demoIndex)
{
    return cats[catIndex]->GetChartDemo(demoIndex);
}

DemoCollection *DemoCollection::Get()
{
    return &instance;
}

