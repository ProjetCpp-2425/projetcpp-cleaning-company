import QtQuick 2.0
import QtLocation 5.9
import QtPositioning 5.9

Rectangle {
    id: window
    width: 640
    height: 480
    visible: true

    property double latitude: 0
    property double longitude: 0
    property Component locationMarker: locmarker

    Plugin {
        id: googlemapview
        name: "osm" // Ensure "osm" plugin is available in your environment
    }

    Map {
        id: mapview
        anchors.fill: parent
        plugin: googlemapview
        center: QtPositioning.coordinate(latitude, longitude)
        zoomLevel: 15
    }

    function setCenterPosition(lati, longi) {
        mapview.center = QtPositioning.coordinate(lati, longi)
        latitude = lati
        longitude = longi
    }

    function setLocationMarking(lati, longi) {
        var item = locationMarker.createObject(window, {
            coordinate: QtPositioning.coordinate(lati, longi)
        });
        mapview.addMapItem(item);
    }

    Component {
        id: locmarker
        MapQuickItem {
            id: markerimg
            anchorPoint.x: image.width / 2
            anchorPoint.y: image.height
            coordinate: position
            sourceItem: Image {
                id: image
                width: 20
                height: 20
                source: "/img/img.png"
            }
        }
    }
}
