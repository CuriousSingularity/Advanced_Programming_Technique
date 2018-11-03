/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPOI.H
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CPOI_H
#define CPOI_H
class CPOI : public CWaypoint {
private:
    t_poi m_type;
    string m_description;
public:

    CPOI(t_poi type, string name, string description, double latitude, double longitude);

    void getAllDataByReference(string& name, double& latitude, double& longitude, t_poi &type, string &description);

    void print();
};
/********************
**  CLASS END
*********************/
#endif /* CPOI_H */
