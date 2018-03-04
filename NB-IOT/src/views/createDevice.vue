<template>
  <div>
    <el-container direction="vertical" class="container">

      <el-row class="navbar">
        <el-header>
        <el-breadcrumb separator-class="el-icon-arrow-right">
          <el-breadcrumb-item :to="{ path: '/' }" replace>首页</el-breadcrumb-item>
          <el-breadcrumb-item >设备管理</el-breadcrumb-item>
          <el-breadcrumb-item :to="{ path: '/deviceList'}" replace>创建设备</el-breadcrumb-item>
        </el-breadcrumb>
        </el-header>

        <el-main>
          <el-row class="delistrow">

            <el-form label-width="100px" class="createdevices" :inline="true" v-bind:model="deviceData">
              <el-row>
                <div class="panel-header">创建设备</div>
              </el-row>
              <el-row class="devicebody">
                <el-col :span="12">
                  <el-form-item label="设备编号">
                    <el-input v-model="deviceData.deviceID" clearable></el-input>
                  </el-form-item>
                </el-col>
                <el-col :span="12">
                  <el-form-item label="设备密码" >
                    <el-input v-model="deviceData.devicePwd" clearable></el-input>
                  </el-form-item>
                </el-col>
                <el-col :span="12">
                  <el-form-item label="设备名称">
                    <el-input v-model="deviceData.deviceName" clearable></el-input>
                  </el-form-item>
                </el-col>
                <el-col :span="12">
                  <el-form-item label="设备地址" >
                    <el-input v-model="deviceData.deviceAddr" clearable></el-input>
                  </el-form-item>
                </el-col>
              </el-row>
              <el-form>
                <el-form-item label="设备描述">
                  <el-input v-model="deviceData.deviceDetail" clearable></el-input>
                </el-form-item>
              </el-form>


              <baidu-map class="map" :center="center" :zoom="15" :scroll-wheel-zoom="true"
                         @moving="syncCenterAndZoom" @moveend="syncCenterAndZoom" @zoomend="syncCenterAndZoom"
                         @click="getPosition">
                <bm-navigation anchor="BMAP_ANCHOR_TOP_RIGHT"></bm-navigation>
                <bm-geolocation anchor="BMAP_ANCHOR_BOTTOM_RIGHT" :showAddressBar="true" :autoLocation="true"></bm-geolocation>
                <bm-city-list anchor="BMAP_ANCHOR_TOP_LEFT"></bm-city-list>
              </baidu-map>
              <el-button type="primary" @click="onSubmit" class="complebtn">创建完成</el-button>
            </el-form>

            <!--<el-input v-model="center.lng"></el-input>-->
            <!--<el-input v-model="center.lat"></el-input>-->
            <!--<el-input v-model="zoom"></el-input>-->

          </el-row>
          </el-main>
      </el-row>

    </el-container>
  </div>
</template>

<script>
  import './../assets/css/createDevice.css'
    export default {
        name: "create-devices",
        data() {
          return {
            deviceData: {
              deviceID: '',
              devicePwd: '',
              deviceName: '',
              deviceAddr: '',
              deviceDetail: ''
            },
            center: {
              lng: 113.409859,
              lat: 23.066113
            },
            zoom: 15
            // styleJson: [
            //   {
            //     "featureType": "all",
            //     "elementType": "geometry",
            //     "stylers": {
            //       "hue": "#007fff",
            //       "saturation": 89
            //     }
            //   },
            //   {
            //     "featureType": "water",
            //     "elementType": "all",
            //     "stylers": {
            //       "color": "#ffffff"
            //     }
            //   }
            // ]
          }
        },
        methods: {
          getPosition(e) {
            console.log("test");
            console.log(e.target.getAddress());
          },
          syncCenterAndZoom(e) {
            const {lng, lat} =  e.target.getCenter();
            this.center.lng = lng;
            this.center.lat = lat;
            this.zoom = e.target.getZoom();

          },
          onSubmit() {
            console.log("创建完成");
          }
        }
    }
</script>

<style scoped>

</style>
