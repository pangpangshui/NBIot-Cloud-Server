<template>
    <el-header style="height: 100px;">
      <!--<div>-->
        <el-row :gutter="20">
          <el-col :span="6">
            <h1 class="hlogo">
              <router-link to="/">
                <img src="./../assets/images/logo.png" alt="NB-Iot Cloud" class="logo"></img>
              </router-link>
            </h1>
          </el-col>
          <el-col :span="6" :offset="12">
        <!--<ul class="nav">-->
          <li class="nav-item">
            <el-input v-model="input" placeholder="搜索" suffix-icon="el-icon-search"></el-input>
          </li>
          <li class="nav-item">
            <router-link to="/test">介绍</router-link>
          </li>
          <li class="nav-item">
            <router-link to="/">API</router-link>
          </li>
          <li class="nav-item">
            <!--<router-link to="/login">登录</router-link>-->
            <!--<router-link to="/login">-->

            <el-dropdown v-if="nickName">
              <span class="el-dropdown-link" v-text="nickName"></span>
              <i class="el-icon-arrow-down el-icon--right" icon="el-icon-arrow-down"></i>
              <el-dropdown-menu slot="dropdown" >
                <router-link to="/users/login">
                  <el-dropdown-item>注销</el-dropdown-item>
                </router-link>
                <router-link to="/backmangementHome">
                  <el-dropdown-item>云平台</el-dropdown-item>
                </router-link>
              </el-dropdown-menu>
            </el-dropdown>

              <el-dropdown v-if="!nickName">
                <span class="el-dropdown-link">
                  登录/注册<i class="el-icon-arrow-down el-icon--right" icon="el-icon-arrow-down"></i>
                </span>
                <el-dropdown-menu slot="dropdown">
                  <router-link to="/users/login">
                    <el-dropdown-item>登录</el-dropdown-item>
                  </router-link>
                  <router-link to="/users/register">
                    <el-dropdown-item>注册</el-dropdown-item>
                  </router-link>
                </el-dropdown-menu>
              </el-dropdown>
            <!--</router-link>-->
          </li>
        <!--</ul>-->
          </el-col>
        </el-row>
      <!--</div>-->
    </el-header>
</template>

<script>
    export default {
        name: "nb-header",
        props: ['nickName'],
        data() {
          return {
            input: '',

          }
        }
    }
</script>

<style scoped>

</style>
