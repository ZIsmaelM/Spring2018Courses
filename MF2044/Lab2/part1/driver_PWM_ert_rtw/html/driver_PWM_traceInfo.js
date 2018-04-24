function RTW_Sid2UrlHash() {
	this.urlHashMap = new Array();
	/* <Root>/Constant */
	this.urlHashMap["driver_PWM:4"] = "driver_PWM.c:35,41,130&driver_PWM.h:87&driver_PWM_data.c:26";
	/* <Root>/S-Function Builder */
	this.urlHashMap["driver_PWM:1"] = "driver_PWM.c:34,40,44,129,133&driver_PWM.h:81";
	this.getUrlHash = function(sid) { return this.urlHashMap[sid];}
}
RTW_Sid2UrlHash.instance = new RTW_Sid2UrlHash();
function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "driver_PWM"};
	this.sidHashMap["driver_PWM"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<Root>/Constant"] = {sid: "driver_PWM:4"};
	this.sidHashMap["driver_PWM:4"] = {rtwname: "<Root>/Constant"};
	this.rtwnameHashMap["<Root>/S-Function Builder"] = {sid: "driver_PWM:1"};
	this.sidHashMap["driver_PWM:1"] = {rtwname: "<Root>/S-Function Builder"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
