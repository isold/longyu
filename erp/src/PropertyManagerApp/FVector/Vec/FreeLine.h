#pragma once

#include "Outlined.h"

class CFreeLine : public COutlined
{
public:
	CFreeLine(CVecWnd *pWnd = NULL);
	virtual ~CFreeLine(void);

	DECLARE_TYPE(FreeLine);

	virtual int HitTest(CPointF point,BOOL bSelect);
	virtual HCURSOR GetCursor(int nHitTest);

	virtual void InitDrag(CPointF point);
	virtual void InitReDrag(CPointF point);
	virtual void InitDragging(CPointF point);
	virtual void InitEndDrag(CPointF point);
	virtual BOOL InitPauseDrag(CPointF point);

	virtual BOOL OnDragStart(int nHitTest,CPointF point);
	virtual void OnDrag(int nHitTest,CPointF point);
	virtual BOOL OnDragEnd(int nHitTest,CPointF point);

	virtual void Draw(CDC *pDC);
	virtual void DrawSelect(CDC *pDC);

	virtual void GetBoundsRect(CRectF &rect) const;
	virtual void SetBoundsRect(const CRectF &rect);

	virtual CElem* Clone(void) const;

	const CFPoints& GetPoints(void) const;
	void SetPoints(const CFPoints &pts);

	void GetPoints(CPoints &pts) const;
	void SetPoints(const CPoints &pts);

private:
	
	CFPoints m_pts;
	CRectF m_rcBounds;
};


inline const CFPoints& CFreeLine::GetPoints(void) const {
	return m_pts;
}
