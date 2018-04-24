function CodeDefine() { 
this.def = new Array();
this.def["IsrOverrun"] = {file: "ert_main_c.html",line:27,type:"var"};
this.def["OverrunFlag"] = {file: "ert_main_c.html",line:28,type:"var"};
this.def["rt_OneStep"] = {file: "ert_main_c.html",line:29,type:"fcn"};
this.def["main"] = {file: "ert_main_c.html",line:57,type:"fcn"};
this.def["driver_PWM_DW"] = {file: "driver_PWM_c.html",line:25,type:"var"};
this.def["driver_PWM_M_"] = {file: "driver_PWM_c.html",line:28,type:"var"};
this.def["driver_PWM_M"] = {file: "driver_PWM_c.html",line:29,type:"var"};
this.def["driver_PWM_step"] = {file: "driver_PWM_c.html",line:32,type:"fcn"};
this.def["driver_PWM_initialize"] = {file: "driver_PWM_c.html",line:79,type:"fcn"};
this.def["driver_PWM_terminate"] = {file: "driver_PWM_c.html",line:147,type:"fcn"};
this.def["DW_driver_PWM_T"] = {file: "driver_PWM_h.html",line:82,type:"type"};
this.def["P_driver_PWM_T"] = {file: "driver_PWM_types_h.html",line:26,type:"type"};
this.def["RT_MODEL_driver_PWM_T"] = {file: "driver_PWM_types_h.html",line:29,type:"type"};
this.def["driver_PWM_P"] = {file: "driver_PWM_data_c.html",line:24,type:"var"};
this.def["chunk_T"] = {file: "multiword_types_h.html",line:27,type:"type"};
this.def["uchunk_T"] = {file: "multiword_types_h.html",line:28,type:"type"};
this.def["int8_T"] = {file: "rtwtypes_h.html",line:51,type:"type"};
this.def["uint8_T"] = {file: "rtwtypes_h.html",line:52,type:"type"};
this.def["int16_T"] = {file: "rtwtypes_h.html",line:53,type:"type"};
this.def["uint16_T"] = {file: "rtwtypes_h.html",line:54,type:"type"};
this.def["int32_T"] = {file: "rtwtypes_h.html",line:55,type:"type"};
this.def["uint32_T"] = {file: "rtwtypes_h.html",line:56,type:"type"};
this.def["real32_T"] = {file: "rtwtypes_h.html",line:57,type:"type"};
this.def["real64_T"] = {file: "rtwtypes_h.html",line:58,type:"type"};
this.def["real_T"] = {file: "rtwtypes_h.html",line:64,type:"type"};
this.def["time_T"] = {file: "rtwtypes_h.html",line:65,type:"type"};
this.def["boolean_T"] = {file: "rtwtypes_h.html",line:66,type:"type"};
this.def["int_T"] = {file: "rtwtypes_h.html",line:67,type:"type"};
this.def["uint_T"] = {file: "rtwtypes_h.html",line:68,type:"type"};
this.def["ulong_T"] = {file: "rtwtypes_h.html",line:69,type:"type"};
this.def["char_T"] = {file: "rtwtypes_h.html",line:70,type:"type"};
this.def["uchar_T"] = {file: "rtwtypes_h.html",line:71,type:"type"};
this.def["byte_T"] = {file: "rtwtypes_h.html",line:72,type:"type"};
this.def["creal32_T"] = {file: "rtwtypes_h.html",line:82,type:"type"};
this.def["creal64_T"] = {file: "rtwtypes_h.html",line:87,type:"type"};
this.def["creal_T"] = {file: "rtwtypes_h.html",line:92,type:"type"};
this.def["cint8_T"] = {file: "rtwtypes_h.html",line:99,type:"type"};
this.def["cuint8_T"] = {file: "rtwtypes_h.html",line:106,type:"type"};
this.def["cint16_T"] = {file: "rtwtypes_h.html",line:113,type:"type"};
this.def["cuint16_T"] = {file: "rtwtypes_h.html",line:120,type:"type"};
this.def["cint32_T"] = {file: "rtwtypes_h.html",line:127,type:"type"};
this.def["cuint32_T"] = {file: "rtwtypes_h.html",line:134,type:"type"};
this.def["pointer_T"] = {file: "rtwtypes_h.html",line:152,type:"type"};
this.def["PWM_Driver_Outputs_wrapper"] = {file: "PWM_Driver_wrapper_c.html",line:35,type:"fcn"};
this.def["PWM_Driver_Update_wrapper"] = {file: "PWM_Driver_wrapper_c.html",line:62,type:"fcn"};
this.def["rtDataTypeSizes"] = {file: "driver_PWM_dt_h.html",line:23,type:"var"};
this.def["rtDataTypeNames"] = {file: "driver_PWM_dt_h.html",line:41,type:"var"};
this.def["rtBTransitions"] = {file: "driver_PWM_dt_h.html",line:59,type:"var"};
this.def["rtBTransTable"] = {file: "driver_PWM_dt_h.html",line:64,type:"var"};
this.def["rtPTransitions"] = {file: "driver_PWM_dt_h.html",line:70,type:"var"};
this.def["rtPTransTable"] = {file: "driver_PWM_dt_h.html",line:75,type:"var"};
this.def["getLoopbackIP"] = {file: "MW_target_hardware_resources_h.html",line:11,type:"var"};
}
CodeDefine.instance = new CodeDefine();
var testHarnessInfo = {OwnerFileName: "", HarnessOwner: "", HarnessName: "", IsTestHarness: "0"};
var relPathToBuildDir = "../ert_main.c";
var fileSep = "\\";
var isPC = true;
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["ert_main_c.html"] = "../ert_main.c";
	this.html2Root["ert_main_c.html"] = "ert_main_c.html";
	this.html2SrcPath["driver_PWM_c.html"] = "../driver_PWM.c";
	this.html2Root["driver_PWM_c.html"] = "driver_PWM_c.html";
	this.html2SrcPath["driver_PWM_h.html"] = "../driver_PWM.h";
	this.html2Root["driver_PWM_h.html"] = "driver_PWM_h.html";
	this.html2SrcPath["driver_PWM_private_h.html"] = "../driver_PWM_private.h";
	this.html2Root["driver_PWM_private_h.html"] = "driver_PWM_private_h.html";
	this.html2SrcPath["driver_PWM_types_h.html"] = "../driver_PWM_types.h";
	this.html2Root["driver_PWM_types_h.html"] = "driver_PWM_types_h.html";
	this.html2SrcPath["driver_PWM_data_c.html"] = "../driver_PWM_data.c";
	this.html2Root["driver_PWM_data_c.html"] = "driver_PWM_data_c.html";
	this.html2SrcPath["multiword_types_h.html"] = "../multiword_types.h";
	this.html2Root["multiword_types_h.html"] = "multiword_types_h.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "rtwtypes_h.html";
	this.html2SrcPath["PWM_Driver_wrapper_c.html"] = "../../PWM_Driver_wrapper.c";
	this.html2Root["PWM_Driver_wrapper_c.html"] = "PWM_Driver_wrapper_c.html";
	this.html2SrcPath["driver_PWM_dt_h.html"] = "../driver_PWM_dt.h";
	this.html2Root["driver_PWM_dt_h.html"] = "driver_PWM_dt_h.html";
	this.html2SrcPath["rtmodel_h.html"] = "../rtmodel.h";
	this.html2Root["rtmodel_h.html"] = "rtmodel_h.html";
	this.html2SrcPath["MW_target_hardware_resources_h.html"] = "../MW_target_hardware_resources.h";
	this.html2Root["MW_target_hardware_resources_h.html"] = "MW_target_hardware_resources_h.html";
	this.getLink2Src = function (htmlFileName) {
		 if (this.html2SrcPath[htmlFileName])
			 return this.html2SrcPath[htmlFileName];
		 else
			 return null;
	}
	this.getLinkFromRoot = function (htmlFileName) {
		 if (this.html2Root[htmlFileName])
			 return this.html2Root[htmlFileName];
		 else
			 return null;
	}
}
Html2SrcLink.instance = new Html2SrcLink();
var fileList = [
"ert_main_c.html","driver_PWM_c.html","driver_PWM_h.html","driver_PWM_private_h.html","driver_PWM_types_h.html","driver_PWM_data_c.html","multiword_types_h.html","rtwtypes_h.html","PWM_Driver_wrapper_c.html","driver_PWM_dt_h.html","rtmodel_h.html","MW_target_hardware_resources_h.html"];
