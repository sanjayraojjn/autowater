import { StyleSheet } from "react-native";
import { PRIMARY_COLOR, PRIMARY_TEXT_COLOR, ROW, SECONDARY_TEXT_COLOR } from "./styles";
import Constants from "expo-constants";

export const styles = StyleSheet.create({
    container: {
        flex: 1,
        paddingTop: Constants.statusBarHeight,
    },
    centeralign: {
        justifyContent: "flex-end",
        alignItems: "center"
    },
    textcolor:{
        color: "white"
    },
    textfontfamily: {
        //fontFamily: 'Cochin',
    },
    titlefont: {
        fontSize: 20,
        fontWeight: 'bold',
    },
    marginview: {
        margin: 20
    },
    header: {
        padding: 15,
        marginBottom: 10,
    },
    headertitle: {
        fontWeight: "bold",
        fontSize: 24,
        color: PRIMARY_COLOR,
    },
    listitem: {
        flexDirection: "row",
        margin: 15,
    },
    deviceicon: {
        width: 60,
        height: 60,
        borderRadius: 6,
        marginRight: 15,
      },
    devicename: {
        fontWeight: "bold",
        fontSize: 16,
        lineHeight: 24,
        color: PRIMARY_TEXT_COLOR,
    },
    deviceinfo: {
        ...ROW,
        flex: 1,
        marginTop: 10,
    },
    macaddress: {
        fontSize: 14,
        color: SECONDARY_TEXT_COLOR,
    },
    ipaddress: {
        fontSize: 14,
        color: SECONDARY_TEXT_COLOR,
    },
    actioninfo: {
        flexDirection: "row",
        justifyContent: "flex-end",
        //flex: 1,
        //marginTop: 10,
    },
    actionicon: {
        width: 30,
        height: 30,
        marginLeft: 20,
        //borderRadius: 3,
        //margin: 10,
      },
    /*buttontext: {
        fontSize: 24,
        //fontFamily: "Cochin",
        color: "white"
    },
    connectbuttoncontainer: {
        width: "100%",
        height: 70,
        backgroundColor: "#fc5c65",
        alignItems: "center",
        justifyContent: "center"
    },
    logostyle: {
        width:250,
        height:250,
        position:"absolute",
        top:70
    },
    monitorbuttoncontainer: {
        width: "100%",
        height: 70,
        backgroundColor: "#4ecdc4",
        alignItems: "center",
        justifyContent: "center"
    },*/
});
