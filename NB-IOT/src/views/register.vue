<template>
  <div>
    <nb-head v-bind:nickName="loginInfo.nickName"></nb-head>
    <el-main>
      <!--<div class="loginContent">-->
      <!--<el-row>-->
      <!--<el-col :span="8">-->
      <!--<el-input placeholder="请输入账号"></el-input>-->
      <!--</el-col>-->
      <!--</el-row>-->
      <!--</div>-->
      <div class="loginContent">
        <el-form :model="loginInfo" status-icon :rules="rules" ref="loginInfo" label-width="100px" class="loginForm">
          <el-form-item label="账号" prop="userName">
            <el-input v-model="loginInfo.userName"></el-input>
          </el-form-item>
          <el-form-item label="密码" prop="userPwd">
            <el-input v-model="loginInfo.userPwd" type="password" auto-complete="off"></el-input>
          </el-form-item>
          <el-form-item label="确认密码" prop="ensurePwd">
            <el-input v-model="loginInfo.ensurePwd" type="password" auto-complete="off" @keyup.enter.native="login"></el-input>
          </el-form-item>
          <el-form-item>
            <el-button type="primary" @click="register">注册</el-button>
            <el-button @click="resetInfo('loginInfo')">重置</el-button>
            <hr>
          </el-form-item>
        </el-form>
      </div>
    </el-main>
  </div>
</template>

<script>
  import nbHeader from "../components/nbHeader";
  import axios from 'axios'
  export default {
    name: "register",
    components: {
      'nb-head': nbHeader,
    },
    data() {
      var validatePwd = (rule, Value, callback) => {
        if (Value === '') {
          callback(new Error("请输入密码"));
        } else {
          if (this.loginInfo.ensurePwd !== '') {
            this.$refs.loginInfo.validateField('ensurePwd');
          }
          callback();
        }
      };

      var validateEnPwd = (rule, value, callback) => {
        if (value === '') {
          callback(new Error('请再次输入密码'));
        } else if (value !== this.loginInfo.userPwd) {
          callback(new Error ('两次输入密码不一致'));
        } else {
          callback();
        }
      };
      return {
        loginInfo: {
          userName: '',
          userPwd: '',
          ensurePwd: '',
          nickName: '',
          errorTip: false
        },
        rules: {
          userName: [
            { required: true, message: '请输入账号', trigger: 'blur' },
            { min:6, max:20, message:'长度6 - 20 个字符', trigger: 'blur' }
          ],
          userPwd: [
            { required: true, message: '请输入密码', trigger: 'blur' },
            { min:6, max:20, message:'长度6 - 20 个字符', trigger: 'blur' },
            { validator: validatePwd, trigger: 'blur'}
          ],
          ensurePwd: [
            { required: true, message: '请确认密码', trigger: 'blur' },
            { min:6, max:20, message:'长度6 - 20 个字符', trigger: 'blur' },
            { validator: validateEnPwd, trigger: 'blur'}
          ]
        }
      };
    },

    methods: {
      //resetFields对整个表单进行重置，将所有字段值重置为初始值并移除校验结果
      resetInfo(userInfo) {
        console.log("clear");
        this.$refs[userInfo].resetFields();
      },

      register() {
        axios.post("/users/register", {
          userName: this.loginInfo.userName,
          userPwd: this.loginInfo.userPwd
        }).then((response) => {
          let res = response.data;
          if (res.status == "0") {
            this.loginInfo.nickName = res.result.userName;
            //this.$router.push('/backmangement');
          } else {

          }
        })
      }
    }
  }
</script>

<style scoped>

</style>
