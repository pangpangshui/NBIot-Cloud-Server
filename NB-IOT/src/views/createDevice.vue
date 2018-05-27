<template>
  <div class="maincontaint" v-loading="loading">
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

            <el-form label-width="100px" class="createdevices" :inline="true" v-bind:model="deviceInfo" :rules="rules">
              <el-row>
                <div class="panel-header">创建设备</div>
              </el-row>
              <el-row class="devicebody">
                <el-col :span="12">
                  <el-form-item label="设备编号" prop="deviceID">
                    <el-input v-model="deviceInfo.deviceID" clearable style="width:400px"></el-input>
                  </el-form-item>
                </el-col>
                <el-col :span="12">
                  <el-form-item label="设备密码" prop="devicePwd">
                    <el-input v-model="deviceInfo.devicePwd" clearable style="width:400px"></el-input>
                  </el-form-item>
                </el-col>
                <el-col :span="12">
                  <el-form-item label="设备名称" prop="deviceName">
                    <el-input v-model="deviceInfo.deviceName" clearable style="width:400px"></el-input>
                  </el-form-item>
                </el-col>
                <el-col :span="12">
                  <el-form-item label="设备地址" prop="deviceAddr">
                    <el-input v-model="deviceInfo.deviceAddr" clearable style="width:400px"></el-input>
                  </el-form-item>
                </el-col>
                <el-form-item label="设备描述" prop="deviceDetail">
                  <el-input v-model="deviceInfo.deviceDetail" clearable style="width:400px"></el-input>
                </el-form-item>
              </el-row>


              <baidu-map class="map" :center="center" :zoom="15" :scroll-wheel-zoom="true"
                           @click="getPosition">
                <bm-marker :position="position" :dragging="true" @click="getPosition" animation="BMAP_ANIMATION_BOUNCE"></bm-marker>
                <bm-navigation anchor="BMAP_ANCHOR_TOP_RIGHT"></bm-navigation>
                <bm-geolocation anchor="BMAP_ANCHOR_BOTTOM_RIGHT" :showAddressBar="true" :autoLocation="true"></bm-geolocation>
                <bm-view class="map"></bm-view>
                <!--<bm-control :offset="{width: '10px', height: '10px'}">-->
                  <!--<bm-auto-complete @searchcomplete="syncCenterAndZoom" v-model="serchaddre" :sugStyle="{zIndex: 1}">-->
                    <!--<el-input placeholder="搜索地址"></el-input>-->
                  <!--</bm-auto-complete>-->
                <!--</bm-control>-->
                <!--<bm-local-search :keyword="serchaddre" :auto-viewport="true"></bm-local-search>-->

              </baidu-map>

              <el-row :gutter="20" type="flex" class="row-bg" justify="end">
              <el-col class="complebtn" :span="6" :offset="18">
                <el-button type="primary" @click="send">创建完成</el-button>
                <el-button type="primary" @click="cancle">取消</el-button>
              </el-col>
              </el-row>

            </el-form>

          </el-row>
          </el-main>
      </el-row>

    </el-container>
  </div>
</template>

<script>
  import './../assets/css/createDevice.css'
  import axios from 'axios'
  import Vue from 'vue'
  import Bus from './../API/bus'
  //Vue.use(Socketio, 'http://127.0.0.1:3001'); //声明时已连接上socketio
    export default {
      name: "create-devices",
      data() {
        return {
          deviceInfo: {
            deviceID: '',
            devicePwd: '',
            deviceName: '',
            deviceAddr: '',
            deviceDetail: '',
            pageid: ''
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
          serchaddre: '',
          connectedUsers: [],
          messages: [],
          message: {
            "type": "",
            "action": "",
            "user": "",
            "text": "",
            "timestamp": ""
          },
          areTyping: [],
          loading: false,
          rules: {
            deviceID: [
              { required: true, trigger: 'blur' }
            ],
            devicePwd: [
              { required: true, message: '请输入密码', trigger: 'blur' }
            ],
            deviceName: [
              { required: true, message: '请输入设备名称', trigger: 'blur' }
            ]
          }
        }
      },
      methods: {
        getPosition(e) {
          const {lng, lat} = e.target.getCenter();
          const posi = e.target.getCenter();
          this.position.lng = lng;
          this.position.lat = lat;

          let geoc = new BMap.Geocoder();
          let pt = e.point;
          geoc.getLocation(pt, (rs) => {
            let addComp = rs.addressComponents;
            //alert(addComp.province + ", " + addComp.city + ", " + addComp.district + ", " + addComp.street + ", " + addComp.streetNumber);
            this.deviceInfo.deviceAddr = addComp.province +  addComp.city + addComp.district + addComp.street + addComp.streetNumber;
          });

        },
        // syncCenterAndZoom(e) {
        //   this.zoom = 15;
        //
        // },
        send() {

          if (this.deviceInfo.deviceID == "" || this.deviceInfo.devicePwd == "" || this.deviceInfo.deviceName == "") {
            this.$message({
              message: '请填写设备ID/设备密码/设备名称',
              center: true,
              type: 'error'
            });
            return;
          }
          // this.loading = true;
          axios.post('/createDevice', {
            deviceID: this.deviceInfo.deviceID,
            devicePwd: this.deviceInfo.devicePwd,
            deviceDetail: this.deviceInfo.deviceDetail,
            deviceAddr: this.deviceInfo.deviceAddr,
            deviceName: this.deviceInfo.deviceName
          }).then((response) => {
            let res = response.data;
            if (res.status == "1") {
              this.deviceInfo.deviceID = res.deviceID;
              //this.$emit('CreateDeviceSuccessfully', this.deviceInfo.deviceID);
              this.$notify({
                title: '创建设备成功',
                message: '设备ID: ' + res.deviceID,
                type: 'success'
              });
              // this.loading = false;
              this.$router.push('/deviceList');
            } else {

            }
            //console.log(deviceid);
          });
        },
        cancle() {
          this.$router.push('/deviceList');
          console.log("cancle");
        }
      },
      created() {
        // Bus.$on('getDeviceInfo', (row) => {
        //   console.log(row);
        //   this.$nextTick(function () {
        //     global.DEVINFO = row;
        //   });
        // });
        // this.deviceInfo = global.DEVINFO;
      },
      mounted() {
        function randomWord(randomFlag, min, max){
          let str = "",
            range = min,
            arr = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
              'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
              'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
              'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
              'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
              'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'];

          // 随机产生
          if(randomFlag){
            range = Math.round(Math.random() * (max-min)) + min;
          }
          for(let i = 0; i<range; i++){
            let pos = Math.round(Math.random() * (arr.length-1));
            str += arr[pos];
          }
          return str;
        }

        this.deviceInfo.deviceID = randomWord(false, 15);
      }
    }
</script>

<style scoped>

</style>
