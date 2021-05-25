//
// Created by rebeater on 2021/1/16.
//

#include "Config.h"

Config::Config(const string &yml_path) {
    root_node = YAML::LoadFile(yml_path);
    imu_filepath = root_node["imu-path"].as<string>();
    imu_para_filepath = root_node["imu-parameter-cfg"].as<string>();
    gnss_filepath = root_node["gnss-path"].as<string>();
    output_filepath = root_node["output-path"].as<string>();
    start_time = root_node["start-time"].as<double>();
    end_time = root_node["end-time"].as<double>();

}

Option Config::getOption() {
    Option opt{};
    opt.imu_format = (ImuFileFormat) root_node["imu-format"].as<int>();
    opt.gnss_format = (GnssFileFormat) root_node["gnss-format"].as<int>();
//    opt.gnss_format = root_node["gnss-format"].as<int>();
    opt.imuPara = getImuPara(imu_para_filepath);
    opt.d_rate = root_node["imu-data-rate"].as<int>();
    for (int i = 0; i < 3; i++) {
        opt.pos_std[i] = root_node["init-pos-std"][i].as<double>();
        opt.vel_std[i] = root_node["init-vel-std"][i].as<double>();
        opt.atti_std[i] = root_node["init-atti-std"][i].as<double>() * _deg;
        opt.angle_bv[i] = root_node["install-angle"][i].as<double>() * _deg;
        opt.lb_wheel[i] = root_node["odo-level-arm"][i].as<double>();
        opt.lb_gnss[i] = root_node["antenna-level-arm"][i].as<double>();
    }
    opt.alignmode = (AlignMode) root_node["alignment-mode"].as<int>();
    opt.nhc_enable = root_node["nhc-enable"].as<bool>();
    opt.nhc_std[0] = root_node["nhc-std"][0].as<double>();
    opt.nhc_std[1] = root_node["nhc-std"][1].as<double>();

    opt.zupt_enable = root_node["zupt-enable"].as<bool>();
    opt.zupta_enable = root_node["zupta-enable"].as<bool>();

    opt.outage_enable = root_node["outage-enable"].as<bool>();
    opt.outage_start = root_node["outage-start"].as<int>();
    opt.outage_stop = root_node["outage-stop"].as<int>();
    opt.outage_time = root_node["outage-time"].as<int>();
    opt.outage_step = root_node["outage-step"].as<int>();
    opt.d_rate = root_node["imu-data-rate"].as<int>();
    return opt;
}

ImuPara Config::getImuPara(const string &imu_para_path) const {
    ImuPara imuPara{};
    YAML::Node imu_para_node = YAML::LoadFile(imu_para_filepath);
//    imu_para_node.IsDefined()
    imuPara.arw = imu_para_node["arw"].as<double>() * _deg / _sqrt_h;
    imuPara.vrw = imu_para_node["vrw"].as<double>() / _sqrt_h;
    for (int i = 0; i < 3; i++) {
        imuPara.gb_std[i] = imu_para_node["gb-std"][i].as<double>() * _deg / _hour;
        imuPara.gs_std[i] = imu_para_node["gs-std"][i].as<double>() * _ppm;
        imuPara.as_std[i] = imu_para_node["as-std"][i].as<double>() * _ppm;
        imuPara.ab_std[i] = imu_para_node["ab-std"][i].as<double>() * _mGal;

        imuPara.gb_ini[i] = imu_para_node["gb-ini"][i].as<double>() * _deg / _hour;
        imuPara.gs_ini[i] = imu_para_node["gs-ini"][i].as<double>() * _ppm;
        imuPara.ab_ini[i] = imu_para_node["ab-ini"][i].as<double>() * _mGal;
        imuPara.as_ini[i] = imu_para_node["as-ini"][i].as<double>() * _ppm;
    }
    imuPara.gt_corr = imu_para_node["gt-corr"].as<double>() * _hour;
    imuPara.at_corr = imu_para_node["gt-corr"].as<double>() * _hour;

    return imuPara;
}

NavOutput Config::getInitNav() {
    static NavOutput nav;
    nav.gpst = root_node["alignment-epoch"][1].as<double>();

    nav.pos[0] = root_node["alignment-epoch"][2].as<double>() * _deg;
    nav.pos[1] = root_node["alignment-epoch"][3].as<double>() * _deg;
    nav.pos[2] = root_node["alignment-epoch"][4].as<double>();

    nav.vn[0] = root_node["alignment-epoch"][5].as<double>();
    nav.vn[1] = root_node["alignment-epoch"][6].as<double>();
    nav.vn[2] = root_node["alignment-epoch"][7].as<double>();

    nav.atti[0] = root_node["alignment-epoch"][8].as<double>() * _deg;
    nav.atti[1] = root_node["alignment-epoch"][9].as<double>() * _deg;
    nav.atti[2] = root_node["alignment-epoch"][10].as<double>() * _deg;

    return nav;
}
