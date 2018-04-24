function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/Constant */
	this.urlHashMap["encoder:4"] = "encoder.c:82&encoder.h:139&encoder_data.c:59";
	/* <Root>/Constant1 */
	this.urlHashMap["encoder:7"] = "encoder.c:52&encoder.h:136&encoder_data.c:56";
	/* <Root>/Discrete PID Controller */
	this.urlHashMap["encoder:15"] = "msg=&block=encoder:15";
	/* <Root>/Mux */
	this.urlHashMap["encoder:14"] = "msg=&block=encoder:14";
	/* <Root>/Pulse
Generator */
	this.urlHashMap["encoder:6"] = "encoder.c:40,49,192&encoder.h:100,118,121,124,127&encoder_data.c:38,41,44,47";
	/* <Root>/S-Function Builder */
	this.urlHashMap["encoder:1"] = "encoder.c:86,102,104,212,214&encoder.h:91";
	/* <Root>/S-Function Builder1 */
	this.urlHashMap["encoder:5"] = "encoder.c:56,90,92,195,197&encoder.h:82,89";
	/* <Root>/Scope */
	this.urlHashMap["encoder:11"] = "encoder.h:94";
	/* <Root>/Scope1 */
	this.urlHashMap["encoder:13"] = "encoder.h:98";
	/* <Root>/Sum */
	this.urlHashMap["encoder:8"] = "encoder.c:51&encoder.h:81";
	/* <Root>/Sum1 */
	this.urlHashMap["encoder:9"] = "encoder.c:60";
	/* <Root>/Sum2 */
	this.urlHashMap["encoder:10"] = "encoder.c:81&encoder.h:84";
	/* <S1>/u */
	this.urlHashMap["encoder:15:1"] = "msg=&block=encoder:15:1";
	/* <S1>/Integral Gain */
	this.urlHashMap["encoder:15:1681"] = "encoder.c:97&encoder.h:106&encoder_data.c:26";
	/* <S1>/Integrator */
	this.urlHashMap["encoder:15:1682"] = "encoder.c:64,96,209&encoder.h:90,130,133&encoder_data.c:50,53";
	/* <S1>/Proportional Gain */
	this.urlHashMap["encoder:15:1680"] = "encoder.c:65&encoder.h:112&encoder_data.c:32";
	/* <S1>/Saturate */
	this.urlHashMap["encoder:15:1683"] = "encoder.c:70,79&encoder.h:83,109,115&encoder_data.c:29,35";
	/* <S1>/Sum */
	this.urlHashMap["encoder:15:1679"] = "encoder.c:63";
	/* <S1>/y */
	this.urlHashMap["encoder:15:10"] = "msg=&block=encoder:15:10";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "encoder"};
	this.sidHashMap["encoder"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<S1>"] = {sid: "encoder:15"};
	this.sidHashMap["encoder:15"] = {rtwname: "<S1>"};
	this.rtwnameHashMap["<Root>/Constant"] = {sid: "encoder:4"};
	this.sidHashMap["encoder:4"] = {rtwname: "<Root>/Constant"};
	this.rtwnameHashMap["<Root>/Constant1"] = {sid: "encoder:7"};
	this.sidHashMap["encoder:7"] = {rtwname: "<Root>/Constant1"};
	this.rtwnameHashMap["<Root>/Discrete PID Controller"] = {sid: "encoder:15"};
	this.sidHashMap["encoder:15"] = {rtwname: "<Root>/Discrete PID Controller"};
	this.rtwnameHashMap["<Root>/Mux"] = {sid: "encoder:14"};
	this.sidHashMap["encoder:14"] = {rtwname: "<Root>/Mux"};
	this.rtwnameHashMap["<Root>/Pulse Generator"] = {sid: "encoder:6"};
	this.sidHashMap["encoder:6"] = {rtwname: "<Root>/Pulse Generator"};
	this.rtwnameHashMap["<Root>/S-Function Builder"] = {sid: "encoder:1"};
	this.sidHashMap["encoder:1"] = {rtwname: "<Root>/S-Function Builder"};
	this.rtwnameHashMap["<Root>/S-Function Builder1"] = {sid: "encoder:5"};
	this.sidHashMap["encoder:5"] = {rtwname: "<Root>/S-Function Builder1"};
	this.rtwnameHashMap["<Root>/Scope"] = {sid: "encoder:11"};
	this.sidHashMap["encoder:11"] = {rtwname: "<Root>/Scope"};
	this.rtwnameHashMap["<Root>/Scope1"] = {sid: "encoder:13"};
	this.sidHashMap["encoder:13"] = {rtwname: "<Root>/Scope1"};
	this.rtwnameHashMap["<Root>/Sum"] = {sid: "encoder:8"};
	this.sidHashMap["encoder:8"] = {rtwname: "<Root>/Sum"};
	this.rtwnameHashMap["<Root>/Sum1"] = {sid: "encoder:9"};
	this.sidHashMap["encoder:9"] = {rtwname: "<Root>/Sum1"};
	this.rtwnameHashMap["<Root>/Sum2"] = {sid: "encoder:10"};
	this.sidHashMap["encoder:10"] = {rtwname: "<Root>/Sum2"};
	this.rtwnameHashMap["<S1>/u"] = {sid: "encoder:15:1"};
	this.sidHashMap["encoder:15:1"] = {rtwname: "<S1>/u"};
	this.rtwnameHashMap["<S1>/Integral Gain"] = {sid: "encoder:15:1681"};
	this.sidHashMap["encoder:15:1681"] = {rtwname: "<S1>/Integral Gain"};
	this.rtwnameHashMap["<S1>/Integrator"] = {sid: "encoder:15:1682"};
	this.sidHashMap["encoder:15:1682"] = {rtwname: "<S1>/Integrator"};
	this.rtwnameHashMap["<S1>/Proportional Gain"] = {sid: "encoder:15:1680"};
	this.sidHashMap["encoder:15:1680"] = {rtwname: "<S1>/Proportional Gain"};
	this.rtwnameHashMap["<S1>/Saturate"] = {sid: "encoder:15:1683"};
	this.sidHashMap["encoder:15:1683"] = {rtwname: "<S1>/Saturate"};
	this.rtwnameHashMap["<S1>/Sum"] = {sid: "encoder:15:1679"};
	this.sidHashMap["encoder:15:1679"] = {rtwname: "<S1>/Sum"};
	this.rtwnameHashMap["<S1>/y"] = {sid: "encoder:15:10"};
	this.sidHashMap["encoder:15:10"] = {rtwname: "<S1>/y"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
