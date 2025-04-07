#ifndef FEATURETYPE_H
#define FEATURETYPE_H

class FeatureType {
public:
    enum type {
        durable,
        tool,
        fuel
    };
};

typedef FeatureType::type feature_type;

#endif //ITEMTYPE_H g
