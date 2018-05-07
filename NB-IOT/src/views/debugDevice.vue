<template>

  <el-row :gutter="2" class="mainRow">
    <el-col :span="20">
      <div class="maincontaint">
        <el-container direction="vertical" class="decontainer">

          <el-row class="navbar">
            <el-header>
              <el-breadcrumb separator-class="el-icon-arrow-right">
                <el-breadcrumb-item :to="{ path: '/' }" replace>首页</el-breadcrumb-item>
                <el-breadcrumb-item >设备管理</el-breadcrumb-item>
                <el-breadcrumb-item :to="{ path: '/debugDevice'}" replace>数据传输</el-breadcrumb-item>
              </el-breadcrumb>
            </el-header>

            <el-main class="debugmain">
              <el-row class="debugrow">

                <el-form label-width="100px" class="debugdevices" :inline="true">
                  <el-row>
                    <div class="panel-header">数据传输</div>
                  </el-row>
                  <el-row class="devicebody">
                    <el-col :span="24">
                    <!--<el-form-item>-->
                      <el-input readonly type="textarea" :rows="18"></el-input>
                    <!--</el-form-item>-->
                    </el-col>
                  </el-row>

                  <el-row class="devicebody" :gutter="30">
                    <el-col :span="20">
                      <el-input v-model="deInfo.deID" placeholder="请输入需要发送的数据"></el-input>
                    </el-col>
                    <el-col :span="4">
                      <el-button>发送</el-button>
                    </el-col>
                  </el-row>

                  <el-row :gutter="30">
                    <el-col :span="6">
                      <!--<el-checkbox-group>-->
                      <el-checkbox label="按16进制发送"></el-checkbox>
                      <el-checkbox label="加回车换行符"></el-checkbox>
                      <!--</el-checkbox-group>-->
                    </el-col>
                    <el-col :span="6">

                    </el-col>
                  </el-row>

                </el-form>

              </el-row>
            </el-main>

          </el-row>
        </el-container>
      </div>
    </el-col>
    <!--<el-button @click="test" type="text" size="small">test</el-button>-->
    <el-col :span="4">
      <el-row>
        <el-card class="box-card" shadow="hover">
          <div class="clearfix" slot="header">
            <span>设备信息</span>
          </div>
          <div class="text item">
            <el-row>
              <label>设备ID:</label>
              <label>{{ deInfo.deviceID }}</label>
            </el-row>
            <el-row>
              <label>设备密码:</label>
              <label>{{ deInfo.devicePwd }}</label>
            </el-row>
            <el-row>
              <label>设备名称:</label>
              <label>{{ deInfo.deviceName }}</label>
            </el-row>
            <el-row>
              <label>设备地址:</label>
              <label>{{ deInfo.deviceAddr }}</label>
            </el-row>
            <el-row>
              <label>设备描述:</label>
              <label>{{ deInfo.deviceDetail }}</label>
            </el-row>
          </div>
        </el-card>
      </el-row>
      <el-row>
        <el-card class="box-card" shadow="hover">
          <div class="clearfix" slot="header">
            <span>其他信息</span>
          </div>
          <div class="text item">
            <el-row>
              <label>注册包:</label>
              <label>ID={{ deInfo.deviceID }}&pwd={{ deInfo.devicePwd }}</label>
            </el-row>
            <el-row>
              <label>单片机的注册包:</label>
              <label>预留</label>
            </el-row>
          </div>
        </el-card>
      </el-row>
    </el-col>
  </el-row>
</template>

<script>
  import Bus from './../API/bus'
  import './../assets/css/debugDevice.css'
  import axios from 'axios'
    export default {
      name: "debug-device",
      data() {
        return {
          deInfo: {
            deviceID: '',
            devicePwd: '',
            deviceName: '',
            deviceAddr: '',
            deviceDetail: ''
          },
          input:''
        }
      },
      methods: {

      },
      created() {
        var self = this;
        Bus.$on('getDeviceInfo', (row) => {
          this.$nextTick(function () {
            // console.log(row);
            //self.deInfo = row;
              global.DEVINFO = row;
          });
        });
        this.deInfo = global.DEVINFO;
        // console.log(this.deInfo);/deviceID=" + this.deInfo.deviceID + "&devicePwd=" + this.deInfo.devicePwd
        axios.post("/debugDevice?deviceID=" + this.deInfo.deviceID + "&devicePwd=" + this.deInfo.devicePwd).then((response) => {
          this.tableData = response.data;
          this.loading = false;
          this.$notify({
            title: '成功',
            message: '成功加载您的设备信息',
            type: 'success'
          });
          console.log(response.data);
        })
      },
      beforeDestroy () {
        Bus.$off('getDeviceInfo', this.deInfo);
      }
    }
</script>

<style scoped>

</style>
