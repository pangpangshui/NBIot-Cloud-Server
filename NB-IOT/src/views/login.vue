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
          <span class="errortip error-show" v-show="loginInfo.errorTip">用户名或密码错误</span>
          <el-form-item label="账号" prop="userName">
            <el-input v-model="loginInfo.userName"></el-input>
          </el-form-item>
          <el-form-item label="密码" prop="userPwd">
            <el-input v-model="loginInfo.userPwd" type="password" auto-complete="off"></el-input>
          </el-form-item>

          <el-form-item>
            <el-button type="primary" @click="login">登录</el-button>
            <el-button @click="resetInfo('loginInfo')">重置</el-button>
            <hr>
            <p>体验NB物联网? 马上去<span class="registerLabel" @click="register">注册</span></p>
          </el-form-item>
        </el-form>
      </div>
    </el-main>
  </div>
</template>

<script>
  import nbHeader from "../components/nbHeader";
  import './../assets/css/login.css';
  import axios from 'axios'
    export default {
        name: "login",
        components: {
          'nb-head': nbHeader,
        },
        data() {
          return {
            loginInfo: {
              userName: '',
              userPwd: '',
              errorTip: false,
              nickName: ''
            },
            rules: {
              userName: [
                { required: true, message: '请输入账号', trigger: 'blur' },
                { min:6, max:20, message:'长度6 - 20 个字符', trigger: 'blur' }
              ],
              userPwd: [
                { required: true, message: '请输入密码', trigger: 'blur' },
                { min:6, max:20, message:'长度6 - 20 个字符', trigger: 'blur' }
              ]
            }
          };
        },

        methods: {
          login() {
            //validate对整个表单进行校验的方法。若不传入回调函数，则会返回一个 promise
            // this.$refs[userinfo].validate((valid) => {
            //   if (valid) {
            //     alert('登录');
            //   } else {
            //     console.log('登陆错误');
            //     return false;
            //   }
            // });

            axios.post("/users/login", {
              userName: this.loginInfo.userName,
              userPwd: this.loginInfo.userPwd
            }).then((response) => {
              let res = response.data;
              if (res.status == "0") {
                this.loginInfo.errorTip = false;
                this.loginInfo.nickName = res.result.userName;
                //this.$router.push('/backmangement');
              } else {
                this.loginInfo.errorTip = true;
              }
            })
          },
          //resetFields对整个表单进行重置，将所有字段值重置为初始值并移除校验结果
          resetInfo(userInfo) {
            console.log("clear");
            this.$refs[userInfo].resetFields();
          },

          register() {
            this.$router.push('/users/register');
          }
        }
    }
</script>

<style scoped>

</style>
