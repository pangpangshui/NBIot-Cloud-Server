<template>
  <div class="maincontaint">
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
                          @moveend="syncCenterAndZoom"  @click="getPosition">
                <bm-marker :position="position" :dragging="true" @click="infoWindowOpen" animation="BMAP_ANIMATION_BOUNCE"></bm-marker>
                <bm-navigation anchor="BMAP_ANCHOR_TOP_RIGHT"></bm-navigation>
                <bm-geolocation anchor="BMAP_ANCHOR_BOTTOM_RIGHT" :showAddressBar="true" :autoLocation="true"></bm-geolocation>
                <bm-city-list anchor="BMAP_ANCHOR_TOP_LEFT"></bm-city-list>
                <!--<bm-control>-->
                  <!--<bm-auto-complete v-model="serchaddre" :sugStyle="{zIndex: 1}">-->
                    <!--<search-field placeholder="搜索地址"></search-field>-->
                  <!--</bm-auto-complete>-->
                <!--</bm-control>-->
                <!--<bm-local-search :keyword="serchaddre" :auto-viewport="true" ></bm-local-search>-->

                <bm-control :offset="{width: '10px', height: '10px'}">
                  <bm-auto-complete v-model="serchaddre" :sugStyle="{zIndex: 1}">
                    <el-input placeholder="搜索地址"></el-input> <!-- 这里指代一个自定义搜索框组件 -->
                  </bm-auto-complete>
                </bm-control>
                <bm-local-search :keyword="serchaddre" :auto-viewport="true" ></bm-local-search>
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
            zoom: 15,
            position: {
              lng: 113.409859,
              lat: 23.066113
            },
            serchaddre: ''

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
            // let map = new BMap.Map();

            const {lng, lat} =  e.target.getCenter();
            const posi =  e.target.getCenter();
            this.position.lng = lng;
            this.position.lat = lat;
            // this.addOverlay(new BMap.Marker(e.target.getCenter());
            // console.log(this.position.lng);
            // console.log(this.position.lat);
            // console.log(posi.value);
            // map.centerAndZoom(this.position, 15);
            // // map.enableScrollWheelZoom();
            // map.clearOverlays();    //清除地图上所有覆盖物
            // map.addOverlay(new BMap.Marker(new BMap.Point(this.position)));    //添加标注


            // let self = this;
            // let geolocation = new BMap.Geolocation();
            // geolocation.getCurrentPosition( (r) => {
            //   if (this.getStatus() == BMAP_STATUS_SUCCESS) {
            //     let geo = new BMap.Geocoder();
            //     geo.getLocation(new BMap.Point(r.point.lng, r.point.lat), (result) => {
            //       if (result) {
            //         self.ADDRESS_DETAIL(result.addressComponents.district + result.addressComponents.street);
            //         self.geohash = result.point.lat + "," + result.point.lng;
            //         self.SAVE_GEOHASH(self.geohash);
            //         self.latitude|= result.point.lat;
            //         self.longitude = result.point.lng;
            //         self.RECOED_ADDRESS({'latitude':result.point.lat, 'longitude':result.point.lng});
            //       }
            //     });
            //   }
            // });
            // console.log(address_detail);
          },
          syncCenterAndZoom(e) {
            const {lng, lat} =  e.target.getCenter();
            this.center.lng = lng;
            this.center.lat = lat;
            this.zoom = e.target.getZoom();
            // console.log(this.center.lng);
            // console.log(this.center.lat);
          },
          onSubmit() {
            console.log("创建完成");
          },
          infoWindowOpen() {
            console.log("tesdt");
          }
        }
    }
</script>

<style scoped>

</style>
