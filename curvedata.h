#ifndef CURVEDATA_H
#define CURVEDATA_H


#include <qwt_plot_canvas.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_directpainter.h>
#include <qwt_curve_fitter.h>
#include <qwt_painter.h>
#include <qevent.h>


class CurveData: public QwtArraySeriesData<QPointF>
{
public:
    CurveData(){}

    virtual QRectF boundingRect() const
    {
        if ( d_boundingRect.width() < 0.0 )
            d_boundingRect = qwtBoundingRect( *this );

        return d_boundingRect;
    }

    inline void append( const QPointF &point )
    {
        d_samples += point;
    }

    void clear()
    {
        d_samples.clear();
        d_samples.squeeze();
        d_boundingRect = QRectF( 0.0, 0.0, -1.0, -1.0 );
    }

    void clearStaleVal(double limit)
    {
        const QVector<QPointF> values = d_samples;
        d_samples.clear();

        int index;
        for(index = values.size() - 1; index >= 0; index-- )
        {
            if(values[index].x() < limit)
                break;
        }

        if ( index > 0 )
            d_samples += (values[index++]);

        while(index < values.size() - 1)
            d_samples += (values[index++]);

        d_boundingRect = QRectF( 0.0, 0.0, -1.0, -1.0 );
    }
};

#endif // CURVEDATA_H
