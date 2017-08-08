/*
 * Navi.h
 *
 * Created: 2017-05-09 10:35:15
 *  Authormodified : Elias H
 */ 


#ifndef NAVI_H_
#define NAVI_H_

// void calculate_rut();
// void print_values();
// void movePositionCalculated();
// void CalculateArloPosition();
// void PositionDifferences();
void calculateArloPosition();
double positionUpdateDiff(double deltaX, double deltaY );
double arloAngleCalculate(double deltaXangle, double deltaYangle);
double deltaArloDiff(double xpositionering1, double xPositionArlo,double ypositionering1, double yPositionArlo);

#endif /* NAVI_H_ */